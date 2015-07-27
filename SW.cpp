#include "SW.hpp"

#include "union_find.hpp"

#include <cmath>
#include <boost/math/special_functions/expm1.hpp>
#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH

namespace ising{

Worker::Worker(alps::Parameters const& params):
  SuperClass(params),
  mcs_(params),
  T_(evaluate("T", params)),
  beta_(1.0/T_),
  J_(params.value_or_default("J", 1.0)),
  p_(-boost::math::expm1(-2.0*beta_*J_)),
  nsites_(num_sites()),
  nbonds_(num_bonds()),
  ene_coeff_(2.0 * J_ / p_),
  spins_(nsites_, 1),
  V2_(nsites_*nsites_)
{
}

void Worker::init_observables(alps::Parameters const&, alps::ObservableSet& obs)
{
  obs << alps::RealObservable("Number of Sites");
  obs << alps::RealObservable("Magnetization^2");
  obs << alps::RealObservable("Magnetization^4");
  obs << alps::RealObservable("|Magnetization|");
  obs << alps::RealObservable("Energy");
  obs << alps::RealObservable("Susceptibility");
  obs << alps::RealObservable("Activated Bonds");
  obs << alps::RealObservable("Activated Bonds^2");
}


void Worker::run(alps::ObservableSet& obs)
{
  ++mcs_;

  // make clusters

  int activated = 0;
  std::vector<union_find::Node> nodes(nsites_, union_find::Node());
  foreach(bond_descriptor b, bonds()){
    const int lsite = source(b);
    const int rsite = target(b);
    if( spins_[lsite] == spins_[rsite] && random_01() < p_){
      union_find::unify(nodes, lsite, rsite);
      ++activated;
    }
  }

  // flip spins

  double ma = 0.0;
  std::vector<int> cluster_size2;
  std::vector<int> cluster_spin;
  int id = 0;
  for(int site=0; site<nsites_; ++site){
    int ri = union_find::root_index(nodes, site);
    union_find::Node &root = nodes[ri];
    if(root.id == -1){
      root.id = id++;
      cluster_size2.push_back(root.size*root.size);
      int s = 2*random_01();
      cluster_spin.push_back(2*s-1);
    }
    spins_[site] = cluster_spin[root.id];
    ma += spins_[site];
  }

  if(!is_thermalized()){
    return;
  }

  // measure 

  const int nc = cluster_size2.size();
  double m2 = 0.0;
  double m4 = 0.0;
  for(int ci=0; ci < nc; ++ci){
    m4 += cluster_size2[ci] * (cluster_size2[ci] + 12*m2);
    m2 += cluster_size2[ci];
  }
  const double V2 = nsites_ * nsites_;
  m2 /= V2;
  m4 /= (V2*V2);

  double ene = nbonds_ * J_ - ene_coeff_ * activated;

  obs["Magnetization^2"] << m2;
  obs["Magnetization^4"] << m4;
  obs["|Magnetization|"] << 1.0*std::abs(ma) / nsites_;
  obs["Susceptibility"] << m2 * nsites_ *  beta_;
  obs["Number of Sites"] << 1.0 * nsites_;
  obs["Energy"] << ene;
  obs["Activated Bonds"] << 1.0*activated;
  obs["Activated Bonds^2"] << 1.0*activated*activated;
}

void Evaluator::evaluate(alps::ObservableSet& obs) const
{
  const double T = alps::evaluate("T", params_);
  const double beta = 1.0/T;
  const double J = params_.value_or_default("J", 1.0);

  alps::RealObsevaluator m2 = obs["Magnetization^2"];
  alps::RealObsevaluator m4 = obs["Magnetization^4"];
  alps::RealObsevaluator ma = obs["|Magnetization|"];
  alps::RealObsevaluator nsites = obs["Number of Sites"];
  alps::RealObsevaluator n = obs["Activated Bonds"];
  alps::RealObsevaluator n2 = obs["Activated Bonds^2"];

  alps::RealObsevaluator binder = m4 / (m2*m2);
  binder.rename("Binder Ratio");
  obs.addObservable(binder);

  alps::RealObsevaluator csus = (m2 - ma * ma) * nsites * beta;
  csus.rename("Connected Susceptibility");
  obs.addObservable(csus);

  const double bj2 = -2.0*beta*J;
  const double coeff = bj2 / (boost::math::expm1(bj2));
  alps::RealObsevaluator spec = (n2 - n*n + std::exp(bj2)*n) * coeff * coeff;
  spec.rename("Specific Heat");
  obs.addObservable(spec);
}

} // end of namespace ising


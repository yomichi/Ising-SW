import numpy as np
import pyalps
import pyalps.plot as plot

#         Observable name : output_prefix
names = { 'Binder Ratio' : 'binder',
          'Susceptibility' : 'sus',
          'Connected Susceptibility' : 'csus',
          'Energy' : 'ene',
          'Magnetization^2' : 'mag2',
          'Magnetization^4' : 'mag4',
          '|Magnetization|' : 'amag',
          'Specific Heat' : 'spec',
          }

result_files = pyalps.getResultFiles(prefix='params')

data = pyalps.loadMeasurements(result_files, names.keys())

for name in names:
  for obs in pyalps.collectXY(data, 'T', name, foreach='L'):
    L = int(obs.props['L'])
    with open('{}-L{}.dat'.format(names[name], L), 'w') as f:
      f.write(plot.convertToText([obs]).replace(' +/- ', ' '))


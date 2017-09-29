# -*- coding: utf-8 -*-

gdb = {
  'alias': 'opera',
  'entity': [
    {
      'alias': 'user',          # the name of the entity
      'mode': 'dynamic',        # [dynamic, fixed], 0: generate dynamicly, 1: generate once
      'tag': {                  # the tag info
        'source': ['sect', 'role'], # from db, must store all the tags
        'count': [2, 3],
        'mode': 'random',         # ['random', 'exclusive', 'respective']
      },
      'ceiling': float('inf'),  # the upper limit
      'suspend': 0,             # the delay time during generation if mode is dynamic
      'stage': [
        {'type': 'gaussian', 'mu': 100, 'sigma': 3},
        {'type': 'gaussian', 'mu': 300, 'sigma': 10}
      ]
    },
    {
      'alias': 'role',
      'mode': 'fixed',
      'ceiling': 5,
      'suspend': 0
    },
    {
      'alias': 'sect',
      'mode': 'fixed',
      'tag': {
        'source': ['role'],
        'count': [1, 1],
        'mode': 'random'
      },
      'ceiling': 20
    },
    {
      'alias': 'actor',
      'mode': 'fixed',
      'tag': {
        'source': ['role', 'sect'],
        'count': [1, 1],
        'mode': 'respective'
      },
      'ceiling': 2030
    },
    {
      'alias': 'video',
      'mode': 'dynamic',
      'tag': {
        'source': ['actor', 'sect', 'role'],
        'count': [1, 2],
        'mode': 'respective'
      },
      'ceiling': float('inf'),
      'suspend': 86400,
      'stage': [
        {'type': 'uniform', 'min': 1, 'max': 10}
      ]
    }
  ],
  'relation': [
    {
      'alias': 'follow',
      'source': 'user',
      'target': 'user',
      'in': {'type': 'power_law', 'lambd': 1.49},
      'out': {'type': 'power_law', 'lambd': [1.15, 2.7]}
    },
    {
      'alias': 'browse_video',
      'source': 'user',
      'target': 'video',
      'in': {'type': 'power_law', 'lambd': 1.37},
      'out': {'type': 'uniform', 'min': 1, 'max': 1000}
    }
  ]
}
# -*- coding: utf-8 -*-

from datetime import datetime

test_scheme = {
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

zhihu_scheme = {
  'alias': 'zhihu',
  'entity': [
    {
      'alias': 'user',
      'mode': 'dynamic',
      'ceiling': 100000,
      'suspend': 0,
      'attr': [
        {'alias': 'gender', 'value': {'type': str, 'range': ['male', 'female']}},
        {'alias': 'industry', 'value': {'type': str, 'range': ['education', 'IT', 'medical', 'manage', 'finance', 'else']}},
        {'alias': 'experience', 'value': {'type': str}}
      ],
      'stage': [
        {'type': 'gaussian', 'mu': 100, 'sigma': 4},
        {'type': 'gaussian', 'mu': 200, 'sigma': 10}
      ]
    },
    {
      'alias': 'question',
      'mode': 'dynamic',
      'ceiling': 200000,
      'suspend': 0,
      'attr': [
        {'alias': 'title', 'value': {'type': str}},
        {'alias': 'pose_time', 'value': {'type': datetime}},
        {'alias': 'class', 'value': {'type': str, 'range': ['game', 'sport', 'history', 'IT', 'work', 'culture', 'science', 'music', 'else']}}
      ],
      'stage': [
        {'type': 'gaussian', 'mu': 200, 'sigma': 3},
        {'type': 'gaussian', 'mu': 500, 'sigma': 10}
      ]
    },
    {
      'alias': 'article',
      'mode': 'dynamic',
      'ceiling': 60000,
      'suspend': 0,
      'attr': [
        {'alias': 'title', 'value': {'type': str}},
        {'alias': 'create_time', 'value': {'type': datetime}},
        {'alias': 'class', 'value': {'type': str, 'range': ['game', 'sport', 'history', 'IT', 'work', 'culture', 'science', 'music', 'else']}}
      ],
      'stage': [
        {'type': 'gaussian', 'mu': 50, 'sigma': 2}
      ]
    },
    {
      'alias': 'column',
      'mode': 'dynamic',
      'ceiling': 10000,
      'suspend': 0,
      'attr': [
        {'alias': 'name', 'value': {'type': str}},
        {'alias': 'create_time', 'value': {'type': datetime}}
      ],
      'stage': [
        {'type': 'gaussian', 'mu': 10, 'sigma': 2}
      ]
    },
    {
      'alias': 'thought',
      'mode': 'dynamic',
      'ceiling': float('inf'),
      'suspend': 0,
      'attr': [
        {'alias': 'content', 'value': {'type': str}},
        {'alias': 'share_time', 'value': {'type': datetime}}
      ],
      'stage': [
        {'type': 'gaussian', 'mu': 100, 'sigma': 2}
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
      'alias': 'pose',
      'source': 'user',
      'target': 'question',
      'in': {'type': 'uniform', 'min': 1, 'max': 1},
      'out': {'type': 'power_law', 'lambd': 1.25}
    },
    {
      'alias': 'publish',
      'source': 'user',
      'target': 'article',
      'in': {'type': 'uniform', 'min': 1, 'max': 1},
      'out': {'type': 'power_law', 'lambd': 1.32}
    },
    {
      'alias': 'create',
      'source': 'user',
      'target': 'column',
      'in': {'type': 'uniform', 'min': 1, 'max': 1},
      'out': {'type': 'power_law', 'lambd': 2.1}
    },
    {
      'alias': 'share',
      'source': 'user',
      'target': 'thought',
      'in': {'type': 'uniform', 'min': 1, 'max': 1},
      'out': {'type': 'power_law', 'lambd': 1.62}
    },
    {
      'alias': 'reply',
      'source': 'user',
      'target': 'question',
      'in': {'type': 'power_law', 'lambd': [1.17, 2.64]},
      'out': {'type': 'power_law', 'lambd': 1.52}
    },
    {
      'alias': 'comment',
      'source': 'user',
      'target': 'thought',
      'in': {'type': 'power_law', 'lambd': 1.53},
      'out': {'type': 'power_law', 'lambd': [1.21, 2.57]}
    },
    {
      'alias': 'contain',
      'source': 'column',
      'target': 'article',
      'in': {'type': 'uniform', 'min': 1, 'max': 1},
      'out': {'type': 'power_law', 'lambd': 1.41}
    }
  ]
}
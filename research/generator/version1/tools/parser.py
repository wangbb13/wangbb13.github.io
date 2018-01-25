# -*- coding: utf-8 -*-

from datetime import datetime

db_miss_alias = 'You miss the key alias of DB.'
db_null_alias = 'The value of key alias can not be null.'
# errors in entity
ent_duplicate = 'The entity alias %s is repeated.'
ent_miss_alias = 'You miss the key alias of entity.'
ent_null_alias = 'The value of key alias in entity can not be null.'
ent_mode_option_err = 'Only dynamic or fixed for mode of entity is legal. In entity %s -> mode.'
ent_tag_src_err = 'There is no entity in DB for tag source. In entity %s -> tag -> source.'
ent_tag_mode_err = 'Optional values for mode of tag: random, respective, exclusive. In entity %s -> tag -> mode.'
ceiling_err = 'The type of ceiling in entity should be int or float and should more than zero. In entity %s -> ceiling.'
suspend_err = 'The type of suspend in entity should be int or float and should more or equal than zero. In entity %s -> suspend.'
# error in relation 
rel_duplicate = 'The relation alias %s is repeated.'
rel_miss_alias = 'You miss the key alias of relation.'
rel_null_alias = 'The value of key alias in relation can not be null.'
rel_src_err = 'The source entity of relation %s is not exist.'
rel_tag_err = 'The target entity of relation %s is not exist.'
# distribution error
gauss_miss_err = 'The parameters for gaussian are mu and sigma.'
power_miss_err = 'The parameter for power law is lambd. It could be a non-negtive float number or a list of two number.'
uniform_miss_err = 'The parameters for unifrom are min and max.'
distr_type_err = 'The type of parameters of distributions should be int or float.'
distr_range_err = 'The value of parameters of distributions should more or equal than zero.'


class ConfigError(Exception):
  def __init__(self, val):
    self.message = val


def distr_legal(distr):
  distr_set = set(['gaussian', 'uniform', 'power_law'])
  try:
    assert distr['type'] in distr_set
  except:
    raise ConfigError('The supported distributions are: gaussian, uniform and power_law')
  if distr['type'] == 'gaussian':
    try:
      assert 'mu' in distr and 'sigma' in distr
    except:
      raise ConfigError(gauss_miss_err)
    try:
      assert (isinstance(distr['mu'], int) or isinstance(distr['mu'], float)) and (isinstance(distr['sigma'], int) or isinstance(distr['sigma'], float))
    except:
      raise ConfigError(distr_type_err)
    try:
      assert distr['mu'] >= 0 and distr['sigma'] >= 0
    except:
      raise ConfigError(distr_range_err)
  elif distr['type'] == 'uniform':
    try:
      assert 'min' in distr and 'max' in distr
    except:
      raise ConfigError(uniform_miss_err)
    try:
      assert (isinstance(distr['min'], int) or isinstance(distr['min'], float)) and (isinstance(distr['max'], int) or isinstance(distr['max'], float))
    except:
      raise ConfigError(distr_type_err)
    try:
      assert distr['min'] >= 0 and distr['max'] >= 0
    except:
      raise ConfigError(distr_range_err)
  else:
    try:
      assert 'lambd' in distr
    except:
      raise ConfigError(power_miss_err)
    try:
      assert (isinstance(distr['lambd'], int) or isinstance(distr['lambd'], float) or (isinstance(distr['lambd'], list) and len(distr['lambd']) == 2))
    except:
      raise ConfigError(power_miss_err + '\n' + distr_type_err)
    try:
      if isinstance(distr['lambd'], int) or isinstance(distr['lambd'], float):
        assert distr['lambd'] >= 0
      else:
        assert distr['lambd'][0] >= 0 and distr['lambd'][1] >= 0
    except:
      raise ConfigError(distr_range_err)


def legal(g_dict):
  try:
    assert 'alias' in g_dict
  except:
    raise ConfigError(db_miss_alias)
  try:
    assert g_dict['alias'] != ''
  except:
    raise ConfigError(db_null_alias)
  ent_set = set()
  ent_mode = set(['dynamic', 'fixed'])
  tag_mode = set(['random', 'exclusive', 'respective'])
  # distr_set = set(['gaussian', 'uniform', 'power_law'])
  # check entities
  # alias
  for e_dict in g_dict['entity']:
    try:
      assert 'alias' in e_dict
    except:
      raise ConfigError(ent_miss_alias)
    try:
      assert e_dict['alias'] != ''
    except:
      raise ConfigError(ent_null_alias)
    try:
      assert e_dict['alias'] not in ent_set
    except:
      raise ConfigError(ent_duplicate % (e_dict['alias']))
    ent_set.add(e_dict['alias'])
  for e_dict in g_dict['entity']:
    # mode
    try:
      assert e_dict['mode'] in ent_mode
    except:
      raise ConfigError(ent_mode_option_err % (e_dict['alias']))
    # tag
    if 'tag' in e_dict:
      try:
        assert isinstance(e_dict['tag']['source'], list)
      except:
        raise ConfigError('The type of source of tag should be list.')
      for ent in e_dict['tag']['source']:
        try:
          assert ent in ent_set
        except:
          raise ConfigError(ent_tag_src_err % (e_dict['alias']))
      try:
        assert e_dict['tag']['mode'] in tag_mode
      except:
        raise ConfigError(ent_tag_mode_err % (e_dict['alias']))
    # attr
    if 'attr' in e_dict:
      try:
        assert isinstance(e_dict['attr'], list)
      except:
        raise ConfigError('the type of attr should be list')
      for one_attr in e_dict['attr']:
        try:
          assert 'alias' in one_attr
          assert isinstance(one_attr['alias'], str)
          assert 'value' in one_attr
          assert 'type' in one_attr['value']
          assert isinstance(one_attr['value']['type'], type)
          if 'range' in one_attr['value']:
            assert isinstance(one_attr['value']['range'], list)
        except:
          raise ConfigError("One attr should be : \{'alias': 'XXX', 'value': \{'type': XXX, 'range'(optional): [...]\}\}")
    # ceiling
    try:
      assert (isinstance(e_dict['ceiling'], int) or isinstance(e_dict['ceiling'], float)) and (e_dict['ceiling'] > 0)
    except:
      raise ConfigError(ceiling_err % (e_dict['alias']))
    if e_dict['mode'] == 'dynamic':
      # suspend
      try:
        assert (isinstance(e_dict['suspend'], int) or isinstance(e_dict['suspend'], float)) and (e_dict['suspend'] >= 0)
      except:
        raise ConfigError(suspend_err % (e_dict['alias']))
      # stage
      try:
        assert isinstance(e_dict['stage'], list)
      except:
        raise ConfigError('The type of stage should be list')
      for distr in e_dict['stage']:
        distr_legal(distr)
  # check relations
  rel_set = set()
  for rel in g_dict['relation']:
    try:
      assert 'alias' in rel
    except:
      raise ConfigError(rel_miss_alias)
    try:
      assert rel['alias'] != ''
    except:
      raise ConfigError(rel_null_alias)
    try:
      assert rel['alias'] not in rel_set
    except:
      raise ConfigError(rel_duplicate % (rel['alias']))
    rel_set.add(rel['alias'])
  for rel in g_dict['relation']:
    try:
      assert rel['source'] in ent_set
    except:
      raise ConfigError(rel_src_err % (rel['alias']))
    try:
      assert rel['target'] in ent_set
    except:
      raise ConfigError(rel_tag_err % (rel['alias']))
    distr_legal(rel['in'])
    distr_legal(rel['out'])


def test():
  from test import test_scheme
  legal(test_scheme)


if __name__ == '__main__':
  test()
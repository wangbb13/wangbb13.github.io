# create time: 2018-04-15
# author: wangbb13
from power_law import NGPowerLaw
from uniform import NGUniform
from gauss import NGGauss
from lognormal import NGLognormal


def get_distribution(d_dict, node, edge_num):
    if d_dict['type'] == 'power_law':
        ins = NGPowerLaw(d_dict['lambda'], d_dict['min-d'], d_dict['max-d'], node, edge_num)
        return ins
    elif d_dict['type'] == 'uniform':
        ins = NGUniform(d_dict['min-d'], d_dict['max-d'], node)
        return ins
    elif d_dict['type'] == 'gaussian':
        ins = NGGauss(d_dict['mu'], d_dict['sigma'], d_dict['min-d'], d_dict['max-d'], node, edge_num)
        return ins
    elif d_dict['type'] == 'lognormal':
        ins = NGLognormal(d_dict['mu'], d_dict['sigma'], d_dict['min-d'], d_dict['max-d'], node, edge_num)
        return ins
    return None

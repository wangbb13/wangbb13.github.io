# -*- coding: utf-8 -*-
import sys
sys.path.append('../')

from .parser import legal
# from .generate import gen_fixed_ent
# from .generate import GenDDR, GenDFR, GenFDR, GenFFR
from .gen_ddr import GenDDR
from .gen_e import GenFE

import gen.macro as macro
import gen.random_str as random_str
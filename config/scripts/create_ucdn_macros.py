# --------------------------
# Imports

from __future__ import print_function

import os
import sys
import re
import zipfile

from textwrap import dedent

if sys.version_info[0] < 3:
    from codecs import open

# --------------------------
# Script Info

SCRIPT = sys.argv[0]

# --------------------------
# Script Arguments

if len(sys.argv) < 4:
    sys.exit("syntax: %s [out_file] [in_directory] [uni_version]" % SCRIPT)

GENFILE = sys.argv[1]
DOWNLOADS = sys.argv[2]
UNIDATA_VERSION = sys.argv[3]

GENDIR = os.path.dirname(os.path.abspath(GENFILE))
if not os.path.exists(GENDIR):
    os.makedirs(GENDIR)

MACRO_FILE = os.path.split(GENFILE)[1].replace(".", "_").upper()
MACRO_SPLIT = os.path.split(os.path.dirname(GENFILE))
MACRO_PATH = MACRO_SPLIT[1].upper() + "_"

if MACRO_SPLIT[0] == "":
    MACRO_PATH = ""

GENMACRO = MACRO_PATH + MACRO_FILE

# --------------------------
# Get Property Values

PROPERTY_VALUES = "PropertyValueAliases%s.txt"

def open_data(template, version):
    local = template % ('-'+version,)
    local = DOWNLOADS + "/" + local
    if local.endswith('.txt'):
        return open(local, encoding='utf-8')
    else:
        return open(local, 'rb')

with open_data(PROPERTY_VALUES, UNIDATA_VERSION) as file:
    fp = open(GENFILE, "w")
    print("/* this file was generated by %s */" % (SCRIPT), file=fp)
    print(file=fp)
    print("#ifndef %s" % GENMACRO, file=fp)
    print("#define %s 1" % GENMACRO, file=fp)
    print(file=fp)
    ea_class = 0
    lb_class = 0
    sc_class = 0
    for line in file:
        m = re.match("^ccc\s*;\s*([0-9]+)\s*;\s*([^\s]+)\s*;\s*([^\s]+)", line)
        if m:
            print("#define UCDN_COMBINING_%s\t%s\t// %s" % (m.group(3).upper(), m.group(1), m.group(2)), file=fp)
        m = re.match("^ea\s*;\s*([^\s]+)\s*;\s*([^\s]+)", line)
        if m:
            print("#define UCDN_EAST_ASIAN_%s\t%s\t// %s" % (m.group(2).upper(), ea_class, m.group(1)), file=fp)
            ea_class += 1
        m = re.match("^lb\s*;\s*([^\s]+)\s*;\s*([^\s]+)", line)
        if m:
            print("#define UCDN_LINEBREAK_%s\t%s\t// %s" % (m.group(2).upper(), lb_class, m.group(1)), file=fp)
            lb_class += 1 
        m = re.match("^sc\s*;\s*([^\s]+)\s*;\s*([^\s]+)", line)
        if m:
            print("#define UCDN_SCRIPT_%s\t%s\t// %s" % (m.group(2).upper(), sc_class, m.group(1)), file=fp)
            sc_class += 1

    print(file=fp)
    print("#endif // %s" % GENMACRO, file=fp)
    print(file=fp)


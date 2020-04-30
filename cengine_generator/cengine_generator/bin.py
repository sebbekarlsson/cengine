from distutils.dir_util import copy_tree
from argparse import ArgumentParser


TEMPLATE_DIR = '/usr/local/share/cengine/res/template/app'


def run():
    parser = ArgumentParser()
    parser.add_argument('name')
    args = parser.parse_args()

    print('Generating project {}...'.format(args.name))

    copy_tree(TEMPLATE_DIR, './{}'.format(args.name))

    print('Done')

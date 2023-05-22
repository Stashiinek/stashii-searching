import client
import argparse

parser = argparse.ArgumentParser(description='search')
parser.add_argument('--fts', type=str, help='for libfts')
args = parser.parse_args()

if args.fts == 'search':
    client.fts_lib.search()
elif args.fts == 'index':
    client.fts_lib.indexator()
else:
    print('Ошибка! Не задан параметр')
import json
import pprint
import copy

def dict_merge(dct, merge_dct):
    """ Recursive dict merge. Inspired by :meth:``dict.update()``, instead of
    updating only top-level keys, dict_merge recurses down into dicts nested
    to an arbitrary depth, updating keys. The ``merge_dct`` is merged into
    ``dct``.
    :param dct: dict onto which the merge is executed
    :param merge_dct: dct merged into dct
    :return: None
    """
    for k, v in merge_dct.items():
        if (k in dct and isinstance(dct[k], dict) and isinstance(merge_dct[k], dict)):  #noqa
            dict_merge(dct[k], merge_dct[k])
        else:
            dct[k] = merge_dct[k]

pp = pprint.PrettyPrinter()
pprint = pp.pprint

n, m = map(int, input().split())
subs = []

for i in range(n):
    line = input().split()
    k1 = int(line[0])
    k2 = int(line[1])
    trigger  = line[2:2 + k1]
    shipment = line[2 + k1:]
    subs.append((trigger, shipment))

offers = dict()

for i in range(m):
    s = input()
    trace = json.loads(s)
    # print()
    # print(trace)
    # print()
    offer_change = trace['offer']
    offer_id = offer_change['id']
    if offer_id not in offers:
        offers[offer_id] = {
            'id': '-1',
            'price': -1,
            'stock_count': -1,
            'partner_content': {
                'title': '##',
                'description': '##',
            },
        }
    old_offer = copy.deepcopy(offers[offer_id])
    dict_merge(offers[offer_id], offer_change)
    new_offer = offers[offer_id]
    # pprint(old_offer)
    # pprint(new_offer)


    for sub in subs:
        intresting = False
        for trigger in sub[0]:
            if trigger == 'id' and old_offer['id'] != new_offer['id']:
                intresting = True
                break
            if trigger == 'price' and old_offer['price'] != new_offer['price']:
                intresting = True
                break
            if trigger == 'stock_count' and old_offer['stock_count'] != new_offer['stock_count']:
                intresting = True
                break
            if trigger == 'partner_content' and old_offer['partner_content'] != new_offer['partner_content']:
                intresting = True
                break
            if trigger == 'title' and old_offer['partner_content']['title'] != new_offer['partner_content']['title']:
                intresting = True
                break
            if trigger == 'description' and old_offer['partner_content']['description'] != new_offer['partner_content']['description']:
                intresting = True
                break
        if not intresting:
            continue
        updates = {'id': new_offer['id']}
        for field in sub[0] + sub[1]:
            if field == 'id' and new_offer['id'] != '-1':
                updates['id'] = new_offer['id']
            if field == 'price' and new_offer['price'] != -1:
                updates['price'] = new_offer['price']
            if field == 'stock_count' and new_offer['stock_count'] != -1:
                updates['stock_count'] = new_offer['stock_count']
            if field == 'partner_content':
                if new_offer['partner_content']['title'] != "##":
                    if 'partner_content' not in updates:
                        updates['partner_content'] = dict()
                    updates['partner_content']['title'] = new_offer['partner_content']['title']
                if new_offer['partner_content']['description'] != "##":
                    if 'partner_content' not in updates:
                        updates['partner_content'] = dict()
                    updates['partner_content']['description'] = new_offer['partner_content']['description']
            if field == 'title' and new_offer['partner_content']['title'] != "##":
                if 'partner_content' not in updates:
                    updates['partner_content'] = dict()
                updates['partner_content']['title'] = new_offer['partner_content']['title']
            if field == 'description' and new_offer['partner_content']['description'] != "##":
                if 'partner_content' not in updates:
                    updates['partner_content'] = dict()
                updates['partner_content']['description'] = new_offer['partner_content']['description']
        msg = {
            'trace_id': trace['trace_id'],
            'offer': updates
        }
        print(json.dumps(msg, separators=(',', ':')))






from vk import User, Community
import csv
import time
import codecs

# Graph with friends
group_screen_name = 'dormitory8hse'
group = Community(group_screen_name)
group.get_info()
group.get_members()
members = set(group.members)
time.sleep(1)

i = 0
written_edges = set()
written_nodes = set()
with codecs.open('data/big_edges.csv', 'w', 'utf-8') as file_edges,\
        codecs.open('data/big_nodes.csv', 'w', 'utf-8') as file_nodes:
    writer_edges = csv.writer(file_edges)
    writer_edges.writerow(['Source', 'Target'])
    writer_nodes = csv.writer(file_nodes)
    writer_nodes.writerow(['Id', 'Label'])

    data = group.get_info_members()
    for member in data:
        # Read a user
        member = data[member]
        user = User(member['id'], member['first_name'], member['last_name'])
        # Write node
        writer_nodes.writerow([user.id, user.last_name + ' ' + user.first_name])
        try:
            if member['deactivated']:
                user.is_closed = 1
        except:
            user.is_closed = member['is_closed']
        # Get friends
        if not user.is_closed:
            try:
                friends = set(user.get_friends())
            except:
                try:
                    time.sleep(2)
                    friends = set(user.get_friends())
                except:
                    time.sleep(1)
                    print(user.id)
            for friend in members.intersection(friends):
                writer_edges.writerow([user.id, friend])

        print(i, 'of', len(group.members))
        i += 1
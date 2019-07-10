import requests
import time

# Example
# https://api.vk.com/method/users.get?user_id=210700286&v=5.52

application_id = 7043491
access_token = 'e7e4504711470200fb4d24b86bd40c4c90645e8127cda44377b3091484f9240a5a32c3e4ce297ac4a687e'
v = 5.101

group_id = 'oldlentach'
user_id = 135979043

# Request constructor
url = 'https://api.vk.com/method/'

grInfo = 'groups.getById'
grSubs = 'groups.getMembers'

userInfo = 'users.get'
userSubs = 'users.getSubscriptions'
userFolls = 'users.getFollowers'
userFrie = 'friends.get'


class Community:
    def __init__(self, id):
        self.id = id
        self.is_closed = None
        self.name = None
        self.screen_name = None
        self.type = None
        self.members = list()

    def get_info(self):
        response = requests.get(url + grInfo, params={
            'access_token': access_token,
            'v': v,
            'group_id': self.id
        }).json()['response'][0]
        self.id = response['id']
        self.name = response['name']
        self.screen_name = response['screen_name']
        self.is_closed = response['is_closed']
        self.type = response['type']

    def get_members(self):
        count = 1001
        while len(self.members) < count:
            try:
                response = requests.get(url + grSubs, params={
                    'access_token': access_token,
                    'v': v,
                    'group_id': self.id,
                    'offset': len(self.members)
                }).json()['response']
            except:
                time.sleep(0.334)
                response = requests.get(url + grSubs, params={
                    'access_token': access_token,
                    'v': v,
                    'group_id': self.id
                }).json()['response']
            for member in response['items']:
                self.members.append(member)
            count = response['count']

    def get_info_members(self, fields=[]):
        result = dict()
        values = [i for i in range(0, len(self.members) - 1, 200)]
        values.append(len(self.members) - 1)
        j = values[0]
        for i in values[1:]:
            try:
                response = requests.get(url + userInfo, params={
                    'access_token': access_token,
                    'v': v,
                    'user_ids': ','.join(map(lambda s: str(s), self.members[j:i])),
                    'fields': ','.join(fields)
                })
                response = response.json()['response']
            except:
                time.sleep(2)
                response = requests.get(url + userInfo, params={
                    'access_token': access_token,
                    'v': v,
                    'user_ids': ','.join(map(lambda s: str(s), self.members[j:i])),
                    'fields': ','.join(fields)
                })
                response = response.json()['response']

            for member in response:
                result[member['id']] = member
            j = i
        return result




class User:
    def __init__(self, id, first_name, last_name):
        self.id = id
        self.first_name = first_name
        self.last_name = last_name
        self.is_closed = None

    def get_info(self):
        response = requests.get(url + userInfo, params={
            'access_token': access_token,
            'v': v,
            'user_ids': self.id
        })
        response = response.json()['response'][0]
        self.first_name = response['first_name']
        self.last_name = response['last_name']
        try:
            self.is_closed = response['is_closed']
        except:
            self.is_closed = True

    def get_subscriptions(self):
        response = requests.get(url + userSubs, params={
            'access_token': access_token,
            'user_id': self.id,
            'v': v,
            'extended': 0
        }).json()['response']
        subscriptions = dict()
        subscriptions['users'] = set(response['users']['items'])
        subscriptions['groups'] = set(response['groups']['items'])
        return subscriptions

    def get_followers(self):
        response = requests.get(url + userFolls, params={
            'access_token': access_token,
            'user_id': self.id,
            'v': v
        }).json()['response']
        followers = response['items']
        return followers

    def get_friends(self):
        response = requests.get(url + userFrie, params={
            'access_token': access_token,
            'v': v,
            'user_id': self.id
        })
        response = response.json()['response']
        return response['items']
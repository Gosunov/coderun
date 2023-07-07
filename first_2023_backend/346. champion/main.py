import requests
import xml.etree.ElementTree as ET

from collections import defaultdict

def get_logins(contest):
    url = f'http://127.0.0.1:7777/view/participants?contest={contest}'
    response = requests.get(url)
    assert response.status_code == 200

    xml = response.text
    root = ET.fromstring(xml)
    logins = []
    for login in root:
        logins.append(login.attrib.get('login'))
    return logins

def get_submissions(contest, login):
    url = f'http://127.0.0.1:7777/view/submissions?contest={contest}&login={login}'
    response = requests.get(url)
    assert response.status_code == 200

    xml = response.text
    root = ET.fromstring(xml)
    submissions = []
    for submission in root:
        submissions.append(submission.attrib)
        submissions[-1]["timestamp"] = int(submissions[-1]["timestamp"])
    return submissions

contest = input()
logins = get_logins(contest)

scoreboard = []
for login in logins:
    submissions = get_submissions(contest, login)
    submissions.sort(key=lambda submission: submission["timestamp"])

    score    = 0
    penalty  = 0
    solved   = set()
    attempts = defaultdict(int)

    for submission in submissions:
        timestamp = submission["timestamp"]
        problem   = submission["problem"]
        verdict   = submission["verdict"]
        if problem in solved:
            continue
        if verdict == 'CE':
            continue
        if verdict == 'OK':
            score += 1
            solved.add(problem)
            penalty += timestamp
            penalty += 20 * attempts[problem]
        else:
            attempts[problem] += 1
    scoreboard.append((login, score, penalty))

scoreboard.sort(key=lambda x: (-x[1], x[2]))

winners = [scoreboard[0]]
for i in range(1, len(scoreboard)):
    if winners[-1][1] == scoreboard[i][1] and winners[-1][2] == scoreboard[i][2]:
        winners.append(scoreboard[i])

print(len(winners))
winners.sort()
for winner in winners:
    print(winner[0])


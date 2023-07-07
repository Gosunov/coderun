#!/usr/bin/python3

import http.server as hs
import sys
import urllib.parse

class Verdict:
    OK = 'OK'
    CE = 'CE'
    WA = 'WA'
    TL = 'TL'
    RE = 'RE'


class Submission:
    def __init__(self, timestamp, problem, verdict):
        self.timestamp = timestamp
        self.problem = problem
        self.verdict = verdict

    def to_xml(self):
        return '<submission timestamp="{}" problem="{}" verdict="{}" />'\
              .format(self.timestamp, self.problem, self.verdict)


class Submissions:
    def __init__(self, submissions):
        self.submissions = submissions

    def to_xml(self):
        return '<submissions>'\
               + ''.join([sub.to_xml() for sub in self.submissions])\
               + '</submissions>'


class Participant:
    def __init__(self, login):
        self.login = login

    def to_xml(self):
        return '<participant login="{}" />'.format(self.login)


class Participants:
    def __init__(self, participants):
        self.participants = participants

    def to_xml(self):
        return '<participants>' \
               + ''.join([part.to_xml() for part in self.participants]) \
               + '</participants>'


def read_input(f):
    contest = f.readline().strip()

    logins = []
    login_submissions = {}

    part_count = int(f.readline())
    for _ in range(part_count):
        login = f.readline().strip()
        submissions_count = int(f.readline())

        submissions = []
        for _ in range(submissions_count):
            submissions.append(Submission(*f.readline().strip().split()))
        logins.append(login)
        login_submissions[login] = Submissions(submissions)

    participants = Participants([Participant(login) for login in logins])
    return contest, participants, login_submissions

class ServerHTTPHandler(hs.BaseHTTPRequestHandler):
    header = '<?xml version="1.0" encoding="UTF-8"?>\n'
    path_view_participants = '/view/participants?'
    path_view_submissions = '/view/submissions?'

    def view_participants(self, query):
        params = urllib.parse.parse_qs(query)
        contest = params.get('contest', [])
        if len(contest) != 1 or contest[0] != ServerHTTPHandler.contest:
            self.send_error(404)
            self.end_headers()
            self.wfile.write((self.header + Participants([]).to_xml()).encode("utf-8"))
            return

        self.send_response(200)
        self.end_headers()
        self.wfile.write((self.header + ServerHTTPHandler.participants.to_xml()).encode("utf-8"))
        return

    def view_submissions(self, query):
        params = urllib.parse.parse_qs(query)
        contest = params.get('contest', [])
        if len(contest) != 1 or contest[0] != ServerHTTPHandler.contest:
            self.send_error(404)
            self.end_headers()
            self.wfile.write((self.header + Submissions([]).to_xml()).encode("utf-8"))
            return
        login = params.get('login', [])
        if len(login) != 1 or login[0] not in ServerHTTPHandler.login_submissions:
            self.send_error(404)
            self.end_headers()
            self.wfile.write((self.header + Submissions([]).to_xml()).encode("utf-8"))
            return
        self.send_response(200)
        self.end_headers()
        self.wfile.write((self.header + ServerHTTPHandler.login_submissions[login[0]].to_xml()).encode("utf-8"))
        return

    def do_GET(self):
        if self.path.startswith(self.path_view_participants):
            self.view_participants(self.path[len(self.path_view_participants):])
        elif self.path.startswith(self.path_view_submissions):
            self.view_submissions(self.path[len(self.path_view_submissions):])
        else:
            print(self.path)
            self.send_error(404)


def run(argv):
    ServerHTTPHandler.contest, ServerHTTPHandler.participants, ServerHTTPHandler.login_submissions = read_input(open(argv[1]))  # input

    server = hs.HTTPServer(('127.0.0.1', 7777), ServerHTTPHandler)
    server.serve_forever()


if __name__ == '__main__':
    run(sys.argv)

#include <bits/stdc++.h>
using namespace std;
#define all(a) (a).begin(), (a).end()

struct Appointment {
    int time;
    int duration;
    vector<string> participants; 
};

bool intersects(Appointment* a, Appointment* b) {
    int l1 = a->time;
    int r1 = a->time + a->duration;
    int l2 = b->time;
    int r2 = b->time + b->duration;
    return (l2 <= l1 && l1 < r2) || (l2 < r1 && r1 <= r2) || (l1 <= l2 && l2 < r1) || (l1 < r2 && r2 <= r1);
}

int int_from_time(const string& s) {
    return ((s[0] - '0') * 10 + (s[1] - '0')) * 60 + (s[3] - '0') * 10 + (s[4] - '0');
}

string time_from_int(int time) {
    char s[6];
    sprintf(s, "%02d:%02d", time / 60, time % 60);
    return s;
}

map<string, vector<Appointment*> > appointments[366];

void solve() {
    int q;
    cin >> q;
    while (q--) {
        string cmd;
        cin >> cmd;
        if (cmd == "APPOINT") {
            int day;
            string time; 
            int duration;
            int k;
            cin >> day >> time >> duration >> k;
            vector<string> participants(k);
            for (int i = 0; i < k; ++i) {
                cin >> participants[i];
            }
            Appointment* appointment = new Appointment{int_from_time(time), duration, participants};

            vector<string> failed;
            for (string participant : participants) {
                for (Appointment* other : appointments[day][participant]) {
                    if (intersects(appointment, other)) {
                        failed.push_back(participant);
                        break;
                    }
                }
            }
            if (failed.empty()) {
                cout << "OK" << '\n';
                for (string participant : participants) {
                    appointments[day][participant].push_back(appointment);
                }
            } else {
                cout << "FAIL" << '\n';
                for (string fail : failed) {
                    cout << fail << ' ';
                }
                cout << '\n';
            }
        }
        if (cmd == "PRINT") {
            int d;
            string p;
            cin >> d >> p;
            sort(all(appointments[d][p]), [](Appointment* a, Appointment* b) {
                return a->time < b->time;
            });
            for (Appointment* a : appointments[d][p]) {
                cout << time_from_int(a->time) << ' ';
                cout << a->duration << ' ';
                for (string participant : a->participants) {
                    cout << participant << ' ';
                }
                cout << '\n';
            }
        }
    } 
}

signed main() {
    // ios::sync_with_stdio(0); cin.tie(0);
    solve();
}
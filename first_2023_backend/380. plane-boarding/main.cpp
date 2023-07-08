#include <bits/stdc++.h>
using namespace std;
#define all(a) (a).begin(), (a).end()

struct Person {
    int a;
    int row;
    int pos;
    bool seated;
    Person(int a, int row, int pos) : a(a), row(row), pos(pos), seated(0) {}
};

void solve() {
    int n;
    cin >> n;
    vector<Person> persons;
    persons.reserve(n);
    map<int, set<char> > mp;
    for (int i = 0; i < n; ++i) {
        int a, row;
        char c;
        scanf("%d %d%c", &a, &row, &c);
        int k = 0;
        if (c == 'A') {
            k += mp[row].count('B');
            k += mp[row].count('C');
        }
        if (c == 'B') {
            k += mp[row].count('C');
        }
        if (c == 'E') {
            k += mp[row].count('D');
        }
        if (c == 'F') {
            k += mp[row].count('E');
            k += mp[row].count('D');
        }
        if (k == 1) {
            a += 5;
        }
        if (k == 2) {
            a += 15;
        }
        mp[row].insert(c);
        persons.emplace_back(a, row + 180, 180 - i);
    }
    reverse(all(persons));

    int time = 0;
    while (!persons.empty()) {
        // cout << time << '\n';
        time++;

        // for (Person person : persons) {
        //     cout << person.pos - 180 << ' ' << person.row - 180 << '\n';
        // }
        // cout << '\n';
        vector<Person> new_persons;
        new_persons.reserve(persons.size());
        n = persons.size();
        for (int i = n - 1; i >= 0; --i) {
            if (persons[i].pos == persons[i].row) {
                if (persons[i].a == 0) {
                    persons[i].seated = true;
                    continue;
                }
                persons[i].a -= 1;
                new_persons.push_back(persons[i]);
            } else if (i == n - 1 || persons[i].pos + 1 != persons[i + 1].pos || persons[i + 1].seated) {
                persons[i].pos += 1;
                new_persons.push_back(persons[i]);
            } else {
                new_persons.push_back(persons[i]);
            }
        }
        persons = new_persons;
        reverse(all(persons));
    }
    cout << time - 1 << '\n';
}

signed main() {
    solve();
}
#include <iostream>
#include <queue>
#include <utility>
//#include <vector>

using namespace std;

int main ( void ) {
    int n, k;
    char rad[2][100000];
    cin >> n >> k;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n; j++) {
            cin >> rad[i][j];
        }
    }

    int visited[2][100000];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 100000; j++) {
            visited[i][j] = 0;
        }
    }

    queue<pair<int, int> > q;
    pair <int, int> s (0,0);

    visited[0][0] = 0;
    q.push(s);
    
    //int distance = 0;
    int found = 0;

    while (!q.empty()) {
        s = q.front();
        q.pop();
        
        //cout << "som na [" << s.first << "][" << s.second << "]\n";

        if (s.second + k >= n || s.second + 1 >= n) {
                //distance++;
                cout << visited[(s.first)][s.second]+1 << endl;
                found = 1;
                break;
        }

        if (rad[(s.first)][s.second + 1] != 'x' && ! visited[(s.first)][s.second + 1]) {
            //cout << "posuvam sa dopredu na [" << s.first << "][" << s.second + 1 << "] s distance [" << visited[(s.first)][s.second]+1 << "]\n";
            visited[(s.first)][s.second + 1] = visited[(s.first)][s.second]+1;
            q.push(pair<int, int>((s.first),s.second + 1));

        }
        if (rad[(s.first)][s.second - 1] != 'x' && s.second - 1 > visited[(s.first)][s.second] && s.second - 1 >= 0 && !visited[(s.first)][s.second - 1]) {
            //cout << "posuvam sa dozadu na [" << s.first << "][" << s.second - 1 << "] s distance [" << visited[(s.first)][s.second]+1 << "]\n";
            visited[(s.first)][s.second - 1] = visited[(s.first)][s.second]+1;
            q.push(pair<int, int>((s.first),s.second - 1));
        }
        if (s.first) {
            if (rad[(s.first - 1)][s.second + k] != 'x' && !visited[(s.first - 1)][s.second + k]) {
                visited[(s.first - 1)][s.second + k] = visited[(s.first)][s.second]+1;
                q.push(pair<int, int>((s.first - 1),s.second + k));
                //cout << "posuvam sa do vedlajsieho radu na [" << s.first - 1 << "][" << s.second + k << "] s distance [" << visited[(s.first)][s.second]+1 << "]\n";
            }
        } else {
            if (rad[(s.first + 1)][s.second + k] != 'x' && !visited[(s.first + 1)][s.second + k]) {
                //cout << "posuvam sa do vedlajsieho radu na [" << s.first + 1 << "][" << s.second + k << "] s distance [" << visited[(s.first)][s.second]+1 << "]\n";
                visited[(s.first + 1)][s.second + k] = visited[(s.first)][s.second]+1;
                q.push(pair<int, int>((s.first + 1),s.second + k));
            }
        }

        //distance++;
        //cout << endl;

    }

    if (!found) {
            cout << -1 << endl;
        }

    //cout << distance << endl;

    return 0;
}

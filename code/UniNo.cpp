#include <iostream>
using namespace std;

int main()
{
    int scelta = 0;
    int S[8] = {0};
    cin >> scelta;

    if ((scelta < 0) || (scelta > 5))
        cout << -1;
    else {
        for (int i = 0; i < 8; ++i) {
            cin >> S[i];
        }

        if (scelta == 0) {
            int decimale = 0;
            int n_zeri = 0;
            for (int i = 0; i < 8; ++i) {
                if (S[i] == 0)
                    n_zeri++;
                decimale <<= 1;
                decimale |= S[i];
            }

            cout << n_zeri << endl << decimale << endl;
        }

        else if (scelta == 1) {
            bool palindroma = true;
            for (int i = 0; i < 4; ++i) {
                palindroma = (S[i] == S[7 - i]);
                if (palindroma == false)
                    break;
            }

            if (palindroma == true)
                cout << 1;
            else
                cout << 0;
        }

        else if (scelta == 2) {
            for (int i = 0; i < 7; ++i) {
                cout << S[i + 1] << ",";
            }
            cout << S[0];
        }

        else if (scelta == 3) {
            int T[4] = {0};
            int decimale = 0;
            for (int i = 0; i < 4; ++i) {
                T[i] = S[i*2] & S[i*2 + 1];
            }

            for (int i = 0; i < 4; ++i) {
                cout << T[i];
                if (i < 3)
                    cout << ",";

                decimale <<= 1;
                decimale |= T[i];
            }
            cout << endl << decimale << endl;
        }

        else if (scelta == 4) {
            int primo_quartetto = 0;
            int secondo_quartetto = 0;
            for (int i = 0; i < 4; ++i) {
                primo_quartetto <<= 1;
                primo_quartetto |= S[i];
            }
            for (int i = 4; i < 8; ++i) {
                secondo_quartetto <<= 1;
                secondo_quartetto |= S[i];
            }

            cout << primo_quartetto << endl << secondo_quartetto << endl;
        }

        else if (scelta == 5) {
            int V[4] = {0};
            int massimo = 0;
            for (int i = 0; i < 4; ++i) {
                V[i] = (S[i*2] << 1) | S[i*2 + 1];
                if (V[i] > massimo)
                    massimo = V[i];
            }

            for (int i = 0; i < 4; ++i) {
                cout << V[i];
                if (i < 3)
                    cout << ",";
            }
            cout << endl << massimo;
        }
    }
}

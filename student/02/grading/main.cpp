#include <iostream>
#include <cmath>

using namespace std;

// Before passing automated tests, do not touch the values of the following
// constants, even if they differ from those you see in Plussa.
// At the end of the course, if you use this program to count your final grade,
// you should update the constants to make them identical with those in Plussa.
unsigned int MAX_N_POINTS = 780;
unsigned int MAX_G_POINTS = 100;


// Add functions if you feel it necessary

int main()
{
    unsigned int n = 0;
    unsigned int g = 0;
    unsigned int p = 0;
    unsigned int e = 0;
    cout << "Enter N points, G points, P points: ";
    cin >> n;
    cin >> g;
    cin >> p;
    cout << "Enter exam grade (if no exam, enter zero): ";
    cin >> e;

    //cout << n << " " << g << " " << p << " " << e << endl;

    bool failed = false;

    double n_g_points = ((double)n + (double)g) / 880.0;
    double n_points = (double)n / 780.0;

//    cout << "n_g_points: " << n_g_points << endl;
//    cout << "n_points: " << n_points << endl;

    double n_g_points_best = max(n_g_points, n_points);
    //cout << "n_g_points_best: " << n_g_points_best << endl;

    if (n_g_points_best < 0.5) {
        n_g_points_best = 0;
        failed = true;
    } else if (n_g_points_best >= 0.5 && n_g_points_best < 0.6) {
        n_g_points_best = 1;
    } else if (n_g_points_best >= 0.6 && n_g_points_best < 0.7) {
        n_g_points_best = 2;
    } else if (n_g_points_best >= 0.7 && n_g_points_best < 0.8) {
        n_g_points_best = 3;
    } else if (n_g_points_best >= 0.8 && n_g_points_best < 0.9) {
        n_g_points_best = 4;
    } else {
        n_g_points_best = 5;
    }

    //cout << "n_g_points_best: " << n_g_points_best << endl;

    int p_points = 0;

    if (p < 51) {
        p_points = 0;
        failed = true;
    } else if (p >= 51 && p < 75) {
        p_points = 1;
    } else if (p >= 75 && p < 125) {
        p_points = 2;
    } else if (p >= 125 && p < 150) {
        p_points = 3;
    } else if (p >= 150 && p < 175) {
        p_points = 4;
    } else {
        p_points = 5;
    }

    //cout << "p_points: " << p_points << endl;

    //calculate average of n, g, and e

    double score = ((double)n_g_points_best + (double)p_points + (double)e) / 3.0;
    //cout << "unrounded score: " << score << endl << endl;
    double rounded_score = round(score);
    int score_as_int = (int)rounded_score;

    //calculate g-limiter

    int g_limiter = 0;

    double g_points = (double)g / 100;


    if (g_points < 0.3) {
        g_limiter = 2;
    } else if (g_points >= 0.3 && g_points < 0.4) {
        g_limiter = 3;
    } else if (g_points >= 0.4 && g_points < 0.5) {
        g_limiter = 4;
    } else {
        g_limiter = 5;
    }

    //cout << "g_limiter: " << g_limiter << endl;

    //calculate final score

    int final_score = 0;

    if (failed) {
        //cout << "failed!" << endl;
        final_score = 0;
    } else {
        final_score = min(score_as_int, g_limiter);
    }

    cout << "The final grade is " << final_score << endl;

    return 0;
}

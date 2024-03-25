#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[]) {
    int n = 8;
    double xpoints[8] = {0.0, 0.4140, 1.4949, 5.0014, 6.5163, 3.9303, 8.4813, 2.6505};
    double ypoints[8] = {0.0, 3.9862, 6.1488, 1.047, 4.6102, 1.4057, 5.0371, 4.1196};

    double greatest = 0;
    double smallest = 0;

    long int g1_index;
    long int g2_index;
    long int s1_index;
    long int s2_index;

    for (int i = 0; i < n - 1; i++) {
        double xroot = xpoints[i];
        double yroot = ypoints[i];
        for (int j = i + 1; j < n; j++) {
            double xcompare = xpoints[j];
            double ycomapre = ypoints[j];

            double xdistance = xroot - xcompare;
            double ydistance = yroot - ycomapre;
            double distance = pow(xdistance,2) + pow(ydistance,2);

            if (distance > greatest) {                
                greatest = distance;
                g1_index = i;
                g2_index = j;            
            }
            
            if (smallest == 0 || (distance < smallest)) {
                smallest = distance;
                s1_index = i;
                s2_index = j;     
            }
        }
    }

    printf("Greatest distance is between (%lf,%lf) and (%lf,%lf)\n", xpoints[g1_index], ypoints[g1_index], xpoints[g2_index], ypoints[g2_index]);
    return 0;
}
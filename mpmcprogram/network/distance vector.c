#include <stdio.h>
#include <stdlib.h>

struct node {
    unsigned dist[20];
    unsigned from[20];
} rt[10];

int main() {

    int n, i, j, k;
    int cm[20][20];

    // Input number of routers
    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    // Input cost matrix
    for(i = 0; i < n; i++) {

        for(j = 0; j < n; j++) {

            if(i == j) {

                cm[i][j] = 0;
                printf("Element #%d%d is 0\n", i + 1, j + 1);

            } else {

                printf("Enter element #%d%d: ", i + 1, j + 1);
                scanf("%d", &cm[i][j]);
            }

            // Initialize routing table
            rt[i].dist[j] = cm[i][j];
            rt[i].from[j] = j;
        }
    }

    // Display cost matrix
    printf("\nCost Matrix:\n");

    for(i = 0; i < n; i++) {

        for(j = 0; j < n; j++) {

            printf("%d\t", cm[i][j]);
        }

        printf("\n");
    }

    // Distance Vector Algorithm
    for(i = 0; i < n; i++) {

        for(j = 0; j < n; j++) {

            for(k = 0; k < n; k++) {

                // Check shorter path exists
                if(rt[i].dist[j] >
                   cm[i][k] + rt[k].dist[j]) {

                    // Update distance
                    rt[i].dist[j] =
                    rt[i].dist[k] + rt[k].dist[j];

                    // Update next hop
                    rt[i].from[j] = k;
                }
            }
        }
    }

    // Display routing tables
    printf("\nRouting Table:\n");

    for(i = 0; i < n; i++) {

        printf("\nFor Router %d\n", i + 1);

        for(j = 0; j < n; j++) {

            printf("Node %d via %d Distance %d\n",
                   j + 1,
                   rt[i].from[j] + 1,
                   rt[i].dist[j]);
        }
    }

    return 0;
}
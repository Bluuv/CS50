#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i=0; i<candidate_count; i++)
    {
        if(strcmp(name,candidates[i])==0)
        {
           ranks[rank]=i;
           return true;
        }
    }
    // TODO
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i=0; i<candidate_count; i++)
    {
        for(int j=0; j<candidate_count; j++)
        {
            if(i<j)
            {
                preferences[ranks[i]][ranks[j]]++;
            }
        }
    }
    // TODO
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for(int i=0; i<candidate_count; i++)
    {
        for(int j=0; j<candidate_count; j++)
        {
            if(preferences[i][j]>preferences[j][i])
            {
                pairs[pair_count].winner=i;
                pairs[pair_count].loser=j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for(int step=0; step<pair_count-1; step++)
    {
        for(int z=0; z<pair_count-step-1; z++)
        {
            if(preferences[pairs[z].winner][pairs[z].loser]<preferences[pairs[z+1].winner][pairs[z+1].loser])
            {
                pair temp=pairs[z];
                pairs[z]=pairs[z+1];
                pairs[z+1]=temp;
            }
        }
    }
    // TODO
    return;
}
bool hasCycle(int winner, int loser)
{
    while(winner!=-1 && winner!=loser)
    {
        bool found=false;
        for(int i=0; i<candidate_count; i++)
        {
            if(locked[i][winner]==true)
            {
                found=true;
                winner=i;
            }
        }
        if (found==false)
        {
            winner=-1;
        }
    }
    if(winner==loser)
    {
        return true;
    }
    return false;
}
// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for(int i=0; i<pair_count; i++)
    {
        if (!hasCycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser]=true;
        }
    }
    // TODO
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for(int j=0; j<candidate_count; j++)
    {
        bool cond=true;
        for(int i=0; i<candidate_count; i++)
        {
            if (locked[i][j]==true)
            {
                cond=false;
            }
        }
        if(cond==true)
        {
            printf("Winner: %s\n", candidates[j]);
            return;
        }
    }
    // TODO
    return;
}
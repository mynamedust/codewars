#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    char cards[5][3];
} Hand;
typedef enum { Win, Loss, Tie } Result;

int index_of(char c)
{
	char cards[13] = "23456789TJQKA";
	for (int i = 0; cards[i]; i++)
	{
		if (c == cards[i])
		return (i);
	}
 	return (-1);
}

Hand* PokerHand (const char *cards)
{
  	Hand *hand = (Hand*)malloc(sizeof(Hand));
	char swap[3];

	for(int i = 0; i < 5; i++){
		hand->cards[i][0] = cards[i * 3];
		hand->cards[i][1] = cards[i * 3 + 1];
		hand->cards[i][2] = '\0';
	}
	for (int i = 0; i < 4; i++)
	{
		if (index_of(hand->cards[i][0]) > index_of(hand->cards[i + 1][0]))
		{
			strcpy(swap, hand->cards[i]);
			strcpy(hand->cards[i], hand->cards[i + 1]);
			strcpy(hand->cards[i + 1], swap);
			i = -1;
		}
	}
	return hand;
}

int	find_duplicates(int c, char cards[5][3], int i)
{
	static int d;

	if (i == 4)
		d = 100;
	if (d == c)
		return (0);
	d = c;
	int	res = 0;
	for (int i = 0; i < 5; i++)
	{
		if (c == cards[i][0])
			res++;
	}
	return (res);
}

int find_combination(Hand* player){
	int	result = 0;

	for (int i = 0; i < 5; i++)
	{
		if (i == 3 && index_of(player->cards[3][0]) == 3 && index_of(player->cards[4][0]) == 12)
			continue;
		if (i < 4 && index_of(player->cards[i][0]) + 1 != index_of(player->cards[i + 1][0]))
			break;
		if (i == 4)
		{
			for (int j = 0; player->cards[j][1] == player->cards[0][1]; j++)
			{
				if (j == 4 && player->cards[0][0] == 'T')
					return (9);
				else if (j == 4)
					return (8);
			}
			return (4);
		}
	}
	for (int i = 0; i < 5; i++)
	{
		int num = find_duplicates(player->cards[i][0], player->cards, i);
		if (num == 4)
			return (7);
		if (num == 3 && result < 3)
		{
			result += 3;
			printf("-TRIPLE-");
		}
		if (num == 2)
		{
			result += 1;
			player->cards[i][0] = '0';
		}
		if (result == 4)
			return (6);
		if (i == 4 && result)
			return (result);
	}
	for (int i = 0; i < 5 && player->cards[i][1] == player->cards[0][1]; i++)
	{
		if (i == 4)
			return (5);
	}
	return (0);
}

Result compare (Hand* player, Hand* opponent) {
	for (int i = 0; i < 5; i++)
		printf("%d ", index_of(player->cards[i][0]));
	printf("player;");
	for (int i = 0; i < 5; i++)
		printf("%d ", index_of(opponent->cards[i][0]));
	printf("opponent;");
	int comb_p1 = find_combination(player);
  	int comb_p2 = find_combination(opponent);
	printf("%d - player score, %d - opponent score; ",comb_p1, comb_p2);
  	if (comb_p1 > comb_p2)
		return (Win);
	if (comb_p1 < comb_p2)
  		return (Loss);
	if (comb_p1 == comb_p2)
	{
		if (player->cards[4][0] > opponent->cards[4][0])
			return (Win);
		if (player->cards[4][0] < opponent->cards[4][0])
			return (Loss);
	}
	return (Tie);
}

int run_test_hands (Hand *player, Hand *opponent, Result outcome) {
  Result result = compare (player, opponent);
  printf("%d - my result;%d - should be; \n",result, outcome);
  return outcome == result;
}

int run_test (const char *player, const char *opponent, Result outcome) {
  	Hand *p = PokerHand (player), *o = PokerHand (opponent);
  	int result = run_test_hands (p, o, outcome);
  	free (p);
	free (o);
 	return result;
}

int main()
{
	// run_test ("2H 3H 4H 5H 6H", "KS AS TS QS JS", Loss);
    // run_test ("2H 3H 4H 5H 6H", "AS AD AC AH JD", Win );
    // run_test ("AS AH 2H AD AC", "JS JD JC JH 3D", Win );
    // run_test ("2S AH 2H AS AC", "JS JD JC JH AD", Loss);
    // run_test ("2S AH 2H AS AC", "2H 3H 5H 6H 7H", Win );
    // run_test ("AS 3S 4S 8S 2S", "2H 3H 5H 6H 7H", Win );
    // run_test ("2H 3H 5H 6H 7H", "2S 3H 4H 5S 6C", Win );
    // run_test ("2S 3H 4H 5S 6C", "3D 4C 5H 6H 2S", Tie );
    // run_test ("2S 3H 4H 5S 6C", "AH AC 5H 6H AS", Win );
    // run_test ("2S 3H 4H 5S AC", "AH AC 5H 6H AS", Win );
    // run_test ("2S 2H 4H 5S 4C", "AH AC 5H 6H AS", Loss);
    // run_test ("2S 2H 4H 5S 4C", "AH AC 5H 6H 7S", Win );
    run_test ("6S AD 7H 4S AS", "AH AC 5H 6H 7S", Loss);
    // run_test ("2S AH 4H 5S KC", "AH AC 5H 6H 7S", Loss);
    // run_test ("2S 3H 6H 7S 9C", "7H 3C TH 6H 9S", Loss);
    // run_test ("4S 5H 6H TS AC", "3S 5H 6H TS AC", Win );
    // run_test ("2S AH 4H 5S 6C", "AD 4C 5H 6H 2C", Tie );
}
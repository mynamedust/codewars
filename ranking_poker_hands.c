#include <stdlib.h>
#include <string.h>

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

int	find_duplicates(int c, char cards[5][3])
{
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
		int num = find_duplicates(player->cards[i][0], player->cards);
		if (num == 4)
			return (7);
		if (num == 3 && result < 3)
		{
			result += 3;
			i += 2;
		}
		if (num == 2)
		{
			result += 1;
			i++;
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
	int comb_p1 = find_combination(player);
  	int comb_p2 = find_combination(opponent);
  	
    if (comb_p1 > comb_p2)
		return (Win);
	if (comb_p1 < comb_p2)
  		return (Loss);
    if (comb_p1 == comb_p2)
    {
		if (comb_p1 % 4 == 0 && comb_p1) {
		if (index_of(player->cards[0][0]) > index_of(opponent->cards[0][0]))
			return (Win);
		if (index_of(player->cards[0][0]) < index_of(opponent->cards[0][0]))
			return (Loss);
		if (index_of(player->cards[4][0]) == 12 && index_of(player->cards[0][0]) == 0)
			return (Loss);
		if (index_of(opponent->cards[4][0]) == 12 && index_of(opponent->cards[0][0]) == 0)
			return (Win);
		return (Tie);
    	}
		for (int i = 4; i >= 0; i--) {
			if (index_of(player->cards[i][0]) > index_of(opponent->cards[i][0]))
				return (Win);
			if (index_of(player->cards[i][0]) < index_of(opponent->cards[i][0]))
				return (Loss);
		}
    }
	return (Tie);
}
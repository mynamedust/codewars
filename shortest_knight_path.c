#include <stdlib.h>
#include <stdio.h>

typedef struct
{
	int	x;
	int	y;
}	point;

typedef	struct s_node
{
	point			p;
	int				range;
	struct s_node	*next;
} t_node;

int	clear_exit(t_node **order, int range)
{
	t_node	*start = *order;

	while (*order)
	{
		start = (*order)->next;
		free(*order);
		*order = start;
	}
	return (range);
}

void	order_addnew(t_node **order, int x, int y, int range)
{
	t_node	*newnode;
	t_node	*start = *order;

	if (x > 8 || x < 1 || y > 8 || y < 1)
		return ;
	while (*order)
	{
		if ((*order)->p.x == x && (*order)->p.y == y)
		{
			*order = start;
			return ;
		}
		if ((*order)->next == NULL)
			break;
		*order = (*order)->next;
	}
	newnode = (t_node *)malloc(sizeof(t_node));
	newnode->next = NULL;
	newnode->p.x = x;
	newnode->p.y = y;
	newnode->range = range;
	(*order)->next = newnode;
	*order = start;
}

short	knight(const char *p1, const char *p2) 
{
	point	start = {p1[0] - 96, p1[1] - '0'};
	point	end = {p2[0] - 96, p2[1] - '0'};
	t_node	*order = (t_node *)malloc(sizeof(t_node));
	t_node	*o_start = order;

	order->next = NULL;
	order->p = start;
	order->range = 0;
	while (order)
	{
		if (order->p.x == end.x && order->p.y == end.y)
			return (clear_exit(&o_start, order->range));
		order_addnew(&order, order->p.x + 1, order->p.y + 2, order->range + 1);
		order_addnew(&order, order->p.x +1, order->p.y - 2, order->range + 1);
		order_addnew(&order, order->p.x +2, order->p.y + 1, order->range + 1);
		order_addnew(&order, order->p.x - 2, order->p.y + 1, order->range + 1);
		order_addnew(&order, order->p.x - 2, order->p.y - 1, order->range + 1);
		order_addnew(&order, order->p.x - 1, order->p.y - 2, order->range + 1);
		order_addnew(&order, order->p.x - 1, order->p.y + 2, order->range + 1);
		order_addnew(&order, order->p.x + 2, order->p.y - 1, order->range + 1);
		order = order->next;
	}
	return (clear_exit(&o_start, order->range));
}

int main()
{
	printf("%d - count\n", knight("a1", "c1")); 
}
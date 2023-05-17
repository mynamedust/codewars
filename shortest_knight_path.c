typedef struct
{
	int	x;
	int	y;
}	point;

typedef	struct s_node
{
	point	p;
	int		range;
	s_node	*next;
} t_node;

void	order_addnew(t_node **order, int x, int y, int range)
{
	t_node	*newnode;

	newnode = *order;
	if (x > 8 || x < 1 || y > 8 || y < 1)
		return ;
	while (newnode)
	{
		if (newnode->p.x == x && newnode->p.y == y)
			return ;
	}
	newnode = (t_node *)malloc(sizeof(t_node));
	newnode->next = NULL;
	newnode->p = {x, y};
	newnode->range = range;
	(*order)->next = newnode;
}

short	knight(const char *p1, const char *p2) {
	point	start = {p1[0] - 96, p1[1] - '0'};
	point	end = {p2[0] - 96, p2[1] - '0'};
	t_node	*order = (node *)malloc(sizeof(t_node));

	order->next = NULL;
	order->p = start;
	order->range = 0;
	while (order)
	{
		if (order->p == end)
			clear_exit(order, order->range);
		order_addnew(&order, start.x + 1, start.y + 2, order->range + 1);
		order_addnew(&order, start.x + 1, start.y - 2, order->range + 1);
		order_addnew(&order, start.x + 2, start.y + 1, order->range + 1);
		order_addnew(&order, start.x + 2, start.y - 2, order->range + 1);
		order = order->next;
	}
}

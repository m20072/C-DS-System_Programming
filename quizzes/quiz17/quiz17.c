node_t* NthElementFromLast(slist_t* list, size_t n)
{
	node_t* current_node = list->head->next; /* due to tail dummy */
	node_t* check_node = list->head;

	while(0 < n)
	{
		current_node = current_node->next;
		--n;
	}

	while(list->tail != current_node)
	{
		current_node = current_node->next;
		check_node = check_node->next;
	}
	return check_node;
}
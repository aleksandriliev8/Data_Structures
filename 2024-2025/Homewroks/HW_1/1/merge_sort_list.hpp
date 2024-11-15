#pragma once
#include "./tab.hpp"

Tab* split(Tab* head)
{
	Tab* slow = head;
	Tab* fast = head->next;

	while (fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
	}

	Tab* mid = slow->next;
	slow->next = nullptr;
	if (mid)
		mid->prev = nullptr;

	return mid;
}

Tab* merge(Tab* left, Tab* right, bool by_url)
{
	Tab dummy("", 0);
	Tab* current = &dummy;

	while (left && right)
	{
		bool state;

		if (by_url)
		{
			state = (left->url < right->url) ||
				(left->url == right->url && left->timestamp <= right->timestamp);
		}
		else
		{
			state = (left->timestamp < right->timestamp) ||
				(left->timestamp == right->timestamp && left->url <= right->url);
		}

		if (state)
		{
			current->next = left;
			left->prev = current;
			left = left->next;
		}
		else
		{
			current->next = right;
			right->prev = current;
			right = right->next;
		}

		current = current->next;
	}

	if (left)
	{
		current->next = left;
		left->prev = current;
	}

	if (right)
	{
		current->next = right;
		right->prev = current;
	}

	if (current->next)
		current->next->prev = current;

	return dummy.next;
}

Tab* mergeSort(Tab* head, bool by_url)
{
	if (!head || !head->next)
		return head;

	Tab* mid = split(head);

	Tab* left = mergeSort(head, by_url);
	Tab* right = mergeSort(mid, by_url);

	return merge(left, right, by_url);
}
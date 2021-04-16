Node* delOdd(Node* head)
{
    Node* current = head;
    Node* prev

    if (head == NULL)
        return NULL;
    
    // removes odd heads until we can look a...head. ba-dum tss
    while (current != NULL && current->data % 2 == 1)
    {
          head = current->next; // adjust head to next value
          free(current); // remove previous odd head
          current = head; // get new head
    }

    // Emptied our list
    if (current == NULL)
        return head;

    // Even head
    while (current->next != NULL && current->next->data % 2 == 1)
    {
        if (current->next->data % 2 == 1)
        {
            head->next = head->next->next; // Skipping element
            free(current); // free the odd in betweener
            current = head;
        }
        else // adjust current
        {
            prev = current;
            current = prev->next;
        }
    }

    return head;     
}   


#include <event_list.h>
#include <stdio.h>
#include <stdlib.h>

void add_event(struct event **event_list, enum event_type event_type, double clock_time, void *content) {
  struct event *event;
  struct event *ptr;
  struct event *prev;
  event = (struct event *) malloc(sizeof(struct event));
  if (!event) {
    fprintf(stderr, "ERROR: malloc fails!\n");
    exit(1);
  }
  event->event_type = event_type;
  event->clock_time = clock_time;
  event->content = content;
  event->next = NULL;
  /* initial */
  if (!(*event_list)) {
    *event_list = event;
    return;
  } 
  /* insert into suitable position */
  prev = NULL;
  for (ptr = *event_list; (ptr != NULL) && (ptr->clock_time < event->clock_time); ptr = ptr->next) {
    prev = ptr;
  }
  event->next = ptr;
  if (!prev) {
    *event_list = event;
  } else {
    prev->next = event;
  }
}

void pop_event(struct event **event_list) {
  if (!(*event_list)) {
    exit(1);
  }
  *event_list = (*event_list)->next;
}

/* return NULL if no event in event list */
struct event *get_event(struct event *event_list) {
  return event_list;
}

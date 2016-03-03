
#ifndef EVENT_LIST_H
#define EVENT_LIST_H

enum event_type {
  ARRIVAL,
  DEPARTURE
};

struct event {
  enum event_type event_type;
  double clock_time;
  void *content;
  struct event *next;
};

/* add event to event list */
void add_event(struct event **event_list, enum event_type event_type, double clock_time, void *content);
/* pop event from event list */
void pop_event(struct event **event_list);
/* get first event in the list */
struct event *get_event(struct event *event_list);

#endif

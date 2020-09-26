all_mutex: send rec
all_sem: send rec_m

send:sender.c
	gcc sender.c -o send -lpthread

rec: mutex_reciever.c
	gcc mutex_reciever.c -o send -lpthread

rec_m: sem_recieve.c
	gcc sem_recieve.c -o send -lpthread
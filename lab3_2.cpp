//Иванчук Евгения, 9894

#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>
#include <fcntl.h>

using namespace std;

bool flag = true;
int pipefd[2];

void* func1(void *arg)
{
	int buf;
	while (flag == 1)
	{
		buf = 9894;
		size_t count = sizeof(int);
		write(pipefd[1], &buf, count);
		sleep(1);
	}
	return NULL;
}

void* func2(void *arg)
{
	int buf;
	while (flag == 1)
	{
		buf = 0;
		size_t count = sizeof(int);
		int rv = read(pipefd[0], &buf, count);
		if (rv == -1)
		{
			sleep(1);
		}
		else
		{
			cout << buf << " ";
			cout.flush();
		}
	}
	return NULL;
}

int main()
{
	pipe2(pipefd, O_NONBLOCK);
	pthread_t th1, th2;
	pthread_create(&th1, NULL, func1, NULL);
	pthread_create(&th2, NULL, func2, NULL);
	getchar();
	flag = false;
	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
	close(pipefd[0]);
	close(pipefd[1]);
	return 0;
}

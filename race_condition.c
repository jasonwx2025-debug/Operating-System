#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// 共享资源和同步变量
int shared_buffer = 0;
int read_count = 0;
sem_t rw_mutex; // 保护缓冲区的锁 (控制写者进入)
sem_t mutex;    // 保护 read_count 的互斥锁

// 读者线程
void* reader(void* arg) {
    int id = *(int*)arg;
    
    // --- 填空区 A：读者进入逻辑 ---
    // 思考：修改 read_count 前需要做什么？
    sem_wait(&mutex);
    read_count++;

    if (read_count == 1) {
       sem_wait(&rw_mutex);
    }
    sem_post(&mutex);

    // 执行读取
    printf("Reader %d: 读取到数据 %d\n", id, shared_buffer);
    usleep(100000); 

    // --- 填空区 B：读者离开逻辑 ---
    sem_wait(&mutex);
    read_count--;
    if (read_count == 0) {
        // 思考：你是最后一个走的读者，该给写者留什么信号？
       sem_post(&rw_mutex);
    }
    sem_post(&mutex);

    return NULL;
}

// 写者线程
void* writer(void* arg) {
    int id = *(int*)arg;
    
    sem_wait(&rw_mutex);

    // 执行写入
    shared_buffer += 5;
    printf("Writer %d: 已更新数据为 %d\n", id, shared_buffer);

    // --- 填空区 D：写者离开逻辑 ---
    sem_post(&rw_mutex);
    return NULL;
}

int main() {
    // 初始化信号量
    sem_init(&mutex, 0, 1);
    sem_init(&rw_mutex, 0, 1);

    pthread_t r1, r2, w1;
    int id1=1, id2=2, id3=3;

    // 创建线程模拟并发
    pthread_create(&r1, NULL, reader, &id1);
    pthread_create(&w1, NULL, writer, &id3);
    pthread_create(&r2, NULL, reader, &id2);

    pthread_join(r1, NULL);
    pthread_join(w1, NULL);
    pthread_join(r2, NULL);

    sem_destroy(&mutex);
    sem_destroy(&rw_mutex);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int vertice1;
    int vertice2;
    struct node* next;
} node_t;

void push(node_t** head, int vertice1, int vertice2) {
    node_t* tmp = (node_t*)calloc(sizeof(node_t), 1);
    if(tmp == NULL) return;
    tmp->vertice1 = vertice1;
    tmp->vertice2 = vertice2;
    tmp->next = (*head);
    (*head) = tmp;
}

/* ЗАПИСЬ СВЯЗЕЙ В ФАЙЛ */
void print_to_file(node_t* head, FILE* file) {
    fprintf(file, "graph graphname {\n");
    while(head != NULL) {
        fprintf(file, "%d", head->vertice1);
        if(head->vertice2 != 0) {
            fprintf(file, " -- ");
            fprintf(file, "%d", head->vertice2);
        }
        fprintf(file, ";\n");
        head = head->next;
    }
    fprintf(file, "}");
}

/* ДОБАВЛЕНИЕ СВЯЗЕЙ МЕЖДУ ВЕРШИНАМИ */
void add_edges(node_t** head) {
    while(1) {
        char c;
        int a = 0;
        int b = 0;
        int i = 0;
        int j = 0;
        int m = 1;
        int k, f;

        /* СЧИТЫВАНИЕ ИЗ КОНСОЛИ*/
        char str[7];
        while((c = getchar()) != '\n') {
            str[i] = c;
            i++;
        }
        //printf("i = %d\n", i);

        /* ПРЕКРАЩЕНИЕ СЧИТЫВАНИЯ РЁБЕР*/
        if(str[0] == '-' && str[1] == '1') {
            break;
        }

        /* НАЙТИ ПОЗИЦИИ РАЗДЕЛИТЕЛЯ*/
        while(str[j] != '-') {
            j++;
        }
        //printf("j = %d\n", j);

        /* ПОЛУЧЕНИЕ ПЕРВОЙ ВЕРШИНЫ*/
        k = j-1;
        while(k != -1) {
            a = a + m*(str[k] - '0');
            m = 10*m;
            k--;
        }
        //printf("a = %d\n", a);

        /* ПОЛУЧЕНИЕ ВТОРОЙ ВЕРШИНЫ*/
        f = i-1;
        m = 1;
        while(f != j) {
            b = b + m*(str[f] - '0');
            m = 10*m;
            f--;
        }
        //printf("b = %d\n", b);

        push(head, a, b);
    }
}

/* ПРОВЕРКА НА ПЕТЛИ */
int loops_counter(node_t* head) {
    int l = 0;
    while(head != NULL) {
        if(head->vertice1 == head->vertice2) l++;
        head = head->next;
    }
    return l;
}

/* ПРОВЕРКА НА КРАТНЫЕ РЁБЕРА */
int multiple_edges_counter(node_t* head) {
    node_t* tmp = head;
    int n = 0;
    while (head != NULL) {
        if(head->vertice2 != 0) n++;
        head = head->next;
    }
    //printf("n = %d\n", n);
    
    int arr[2][n];
    int i = 0;
    while(tmp != NULL) {
        arr[0][i] = tmp->vertice1;
        arr[1][i] = tmp->vertice2;
        i++;
        tmp = tmp->next;
    }

    int m = 0;
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if ((arr[0][i] == arr[0][j]) && (arr[1][i] == arr[1][j])) {
                m++;
            } else if((arr[0][i] == arr[1][j]) && (arr[1][i] == arr[0][j])) {
                m++;
            }
            
        }
    }
    return m;
}

/* СЧЁТЧИК РЁБЕР */
int edge_counter(node_t* head) {
    int n = 0;
    while(head != NULL) {
        if(head->vertice2 != 0) {
            n++;
        }
        head = head->next;
    }
    //printf("rebra = %d\n", n);
    return n;
}

/* СЧЁТЧИК ВЕРШИН */
int vertice_counter(node_t* head) {
    int n = 0;
    node_t* tmp = head;
    while(head != NULL) {
        n++;
        head = head->next;
    }
    //printf("n = %d\n", n);

    int arr[n*2];
    for(int i = 0; i < n*2; i = i + 2) {
        arr[i] = tmp->vertice1;
        arr[i+1] = tmp->vertice2;
        tmp = tmp->next;
    }

    /*for(int i = 0; i < n*2; i++) {
        printf("%d ", arr[i]);
    }*/

    for(int i = 0; i < n*2 - 1; i++) {
        for(int j = i + 1; j < n*2; j++) {
            if(arr[i] != -1 && arr[i] == arr[j]) {
                arr[j] = -1;
            }
        }
    }

    //printf("\n");
    /*for(int i = 0; i < n*2; i++) {
        printf("%d ", arr[i]);
    }*/

    int k = 0;
    for(int i = 0; i < n*2; i++) {
        if(arr[i] != -1 && arr[i] != 0) k++;
    }
    //printf("vershiny = %d\n", k);
    return k;
}

/* ПРОВЕРКА НА СВЯЗНОСТЬ */
int connectivity_check(int v, int e, node_t* head) {
    if(loops_counter(head) || multiple_edges_counter(head) != 0) {
        return -2;
    } else if(e > (v-1)*(v-2)*0.5) {
        return 1;
    } else 
        return -1;
}

int main(void)
{
    node_t* head = NULL;

    FILE *file;
    file = fopen("graph.dot", "w");
    if (file == NULL) {
        printf("Error opening file\n");
        return -1;
    }
    printf("Вводите по типу a-a\n");
    printf("Чтобы остановить, введите -1\n");
    printf("Чтобы добавить изолированную вершину b-\n");
    
    add_edges(&head);
    print_to_file(head, file);
    fclose(file);

    printf("\nEdges = %d\n", edge_counter(head));
    printf("Vertices = %d\n", vertice_counter(head));
    printf("Loops = %d\n", loops_counter(head));
    printf("Multiple edges = %d\n\n", multiple_edges_counter(head));

    if (connectivity_check(vertice_counter(head), edge_counter(head), head) == 1)
        printf("This is a connected graph\n");
    else if(connectivity_check(vertice_counter(head), edge_counter(head), head) == -1)
        printf("This is a DISconnected graph\n");
    else
        printf("This is not a simple graph!\n");

    system("dot -Tpng graph.dot -o graph.png");
    system("graph.png");

    return 0;
}

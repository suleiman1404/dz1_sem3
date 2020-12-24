#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int point1;
    int point2;
    struct node* next;
} node_t;

void push(node_t** head, int point1, int point2) {
    node_t* tmp = (node_t*)calloc(sizeof(node_t), 1);
    if(tmp == NULL) return;
    tmp->point1 = point1;
    tmp->point2 = point2;
    tmp->next = (*head);
    (*head) = tmp;
}

void print_to_file(node_t* head, FILE* file) {
    fprintf(file, "graph {\n");
    while(head != NULL) {
        fprintf(file, "%d", head->point1);
        if(head->point2 != 0) {
            fprintf(file, " -- ");
            fprintf(file, "%d", head->point2);
        }
        fprintf(file, ";\n");
        head = head->next;
    }
    fprintf(file, "}");
}

void add_edges(node_t** head) {
    while(1) {
        char c;
        int a = 0;
        int b = 0;
        int i = 0;
        int j = 0;
        int m = 1;
        int k, f;

        char str[7];
        while((c = getchar()) != '\n') {
            str[i] = c;
            i++;
        }
        if(str[0] == '-' && str[1] == '1') {
            break;
        }
        while(str[j] != '-') {
            j++;
        }
        k = j-1;
        while(k != -1) {
            a = a + m*(str[k] - '0');
            m = 10*m;
            k--;
        }
        f = i-1;
        m = 1;
        while(f != j) {
            b = b + m*(str[f] - '0');
            m = 10*m;
            f--;
        }
        push(head, a, b);
    }
}

int loops_counter(node_t* head) {
    int l = 0;
    while(head != NULL) {
        if(head->point1 == head->point2) l++;
        head = head->next;
    }
    return l;
}

int multiple_edges_counter(node_t* head) {
    node_t* tmp = head;
    int n = 0;
    while (head != NULL) {
        if(head->point2 != 0) n++;
        head = head->next;
    }
    
    int arr[2][n];
    int i = 0;
    while(tmp != NULL) {
        arr[0][i] = tmp->point1;
        arr[1][i] = tmp->point2;
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

int edge_counter(node_t* head) {
    int n = 0;
    while(head != NULL) {
        if(head->point2 != 0) {
            n++;
        }
        head = head->next;
    }
    return n;
}

int point_counter(node_t* head) {
    int n = 0;
    node_t* tmp = head;
    while(head != NULL) {
        n++;
        head = head->next;
    }
    int arr[n*2];
    for(int i = 0; i < n*2; i = i + 2) {
        arr[i] = tmp->point1;
        arr[i+1] = tmp->point2;
        tmp = tmp->next;
    }
    for(int i = 0; i < n*2 - 1; i++) {
        for(int j = i + 1; j < n*2; j++) {
            if(arr[i] != -1 && arr[i] == arr[j]) {
                arr[j] = -1;
            }
        }
    }
    int k = 0;
    for(int i = 0; i < n*2; i++) {
        if(arr[i] != -1 && arr[i] != 0) k++;
    }
    return k;
}

int connectivity_check(int v, int e, node_t* head) {
    if(loops_counter(head) || multiple_edges_counter(head) != 0) {
        return -2;
    } else if(e > (v-1)*(v-2)*0.5) {
        return 1;
    } else
        return -1;
}

int multiple_edges_counter2(node_t* head) {
    int p = point_counter(head);
    int e = edge_counter(head);
    int points[p];
    int points_temp[e];
    int arr[p][p], m=0;
    for(int i=0; i<p; i++){
        points[i] = -1;
        points_temp[i] = 0;
        for(int j=0; j<p; j++){
            arr[i][j] = 0;
        }
    }
    node_t* tmp = head;
    int l=0;
    while (tmp != NULL) {
        points_temp[l++] = tmp->point1;
        points_temp[l++] = tmp->point2;
        tmp = tmp->next;
    }
    l=0;
    int flag=0;
    for(int i=0; i<e; i++){
        for(int j=0; j<p; j++){
            if(points_temp[i] == points[j]){
                flag=1;
            }
        }
        if(flag==0){
            points[l++] = points_temp[i];
        }
    }

    while(head != NULL) {
        int p1=0, p2=0;
        for(int i=0; i<p; i++){
            if(points[i] == head->point1){
                p1 = i;
            }
            if(points[i] == head->point2){
                p2 = i;
            }
        }
        arr[p1][p2]++;
        head = head->next;
    }
    
    for(int i=0; i<p; i++){
        for(int j=0; j<p; j++){
            if(arr[i][j] > 1){
                m++;
            }
        }
    }
    
    for(int i=0; i<p; i++){
        for(int j=0; j<p; j++){
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    return m;
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

    printf("Multiple edges = %d\n\n", multiple_edges_counter2(head));
    int j=connectivity_check(point_counter(head), edge_counter(head), head );
    if (j == -2){
    printf("There are multiple edges");
    }
    else if(j==-1){
        printf("Graph disconected");
    }
    else if(j==1){
        printf("Graph connected");
    }
    return 0;
}

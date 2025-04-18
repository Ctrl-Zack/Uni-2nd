    #include<stdio.h>
    #include<stdlib.h>

    typedef struct node_t {
        int value;
        struct node_t *next;
    } Node;

    typedef struct tumpukan_t {
        Node *_top;
        unsigned _size;
    } Tumpuk;

    void init(Tumpuk *T) {
        T->_top = NULL;
        T->_size = 0;
    }

    _Bool isEmpty(Tumpuk *T) {
        return (T->_top == NULL);
    }

    int pushBack(Tumpuk *T, int value) {
        int ans = 1;
        Node *newNode = (Node *)malloc(sizeof(Node));
        
        if(newNode) {
            newNode->value = value;
            newNode->next = NULL;
            if(isEmpty(T)) {
                T->_top = newNode;
            } else {
                Node *tmp = T->_top;
                while(tmp->next != NULL) {
                    if(tmp->value <= newNode->value) ans++;
                    else ans = 1;
                    tmp = tmp->next;
                }
                if(tmp->value <= newNode->value) ans++;
                else ans = 1;
                tmp->next = newNode;
            }
            T->_size++;
        }
        return ans;
    }

    int main() {
        Tumpuk T;
        init(&T);

        int n, ans = 0;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            int a;
            scanf("%d", &a);
            // printf("yes : %d\n", pushBack(&T, a));
            ans += pushBack(&T, a);
        }
        printf("%d", ans);
        return 0;
    }
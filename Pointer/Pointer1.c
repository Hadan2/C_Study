#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct 
{   char *name;
    int power;    
} Weapon;

typedef struct 
{   char *name;
    int hp; 
    Weapon *weapon;   
} Slime;

Slime* createSlime(const char *name, int hp, const char *weaponName, int weaponPower) {
    Slime* s; // s는 슬라임 객체를 가리키는 포인터
    s = (Slime*)malloc(sizeof(Slime)); // 메모리를 할당해 그 공간을 s가 가리키도록 함
    //1. 이름을 넣는다.
    s->name = (char*)malloc(sizeof(char)*strlen(name)+1);
    // 최대가 10밖에 안되서 이렇게까지 할 필요는 없으나 이런 방법도 연습
    strcpy(s->name, name);
    //2. hp 를 넣는다.
    s->hp = hp;

    Weapon* w; // w는 무기 객체를 가리키는 포인터
    w = (Weapon*)malloc(sizeof(Weapon)); // 메모리를 할당해 그 공간을 s가 가리키도록 함
    //1. 이름을 넣는다.
    w->name = (char*)malloc(sizeof(char)*strlen(weaponName)+1);
    strcpy(w->name, weaponName);
    //2. power 를 넣는다.
    w->power = weaponPower;
    //3. slime 의 weapon 에 넣어준다.
    s->weapon = w;
    
    return s;
    
}

void takeDamage(Slime *s, int damage) {
    s->hp -= damage;
}

Slime* deepCopySlime(Slime *original) {
    Slime* cpy_s = (Slime*)malloc(sizeof(Slime));
    cpy_s->name = (char*)malloc(sizeof(char)*strlen(original->name)+1);
    cpy_s->weapon = (Weapon*)malloc(sizeof(Weapon));
    cpy_s->weapon->name = (char*)malloc(sizeof(char)*strlen(original->weapon->name)+1);

    cpy_s->hp = original->hp;
    // cpy_s->name = original->name; 여기서 1차 틀림 : 얕은 복사
    //cpy_s->weapon->name = original->weapon->name;
    strcpy(cpy_s->name, original->name);
    strcpy(cpy_s->weapon->name, original->weapon->name);
    cpy_s->weapon->power = original->weapon->power;

    return cpy_s;
}

void freeSLime(Slime *s) {
    free(s->name);
    free(s->weapon->name);
    free(s->weapon);
    free(s);
}


int main () {
    int hp, power;
    char *weapon_Name = (char*)malloc(sizeof(char)*11);;
    char *slime_Name = (char*)malloc(sizeof(char)*11);

    printf("슬라임 이름/체력을 입력하세요\n");
    scanf("%10s %d", slime_Name, &hp);

    printf("슬라임 무기의 이름/공격력을 입력하세요\n");
    scanf("%10s %d", weapon_Name, &power);
    // 슬라임/무기 이름은 열 글자로 제한

    Slime *s = createSlime(slime_Name, hp, weapon_Name, power);

    printf("%s %d %s %d\n", s->name, s->hp, s->weapon->name, s->weapon->power);

    

    printf("%s %d %s %d\n", s->name, s->hp, s->weapon->name, s->weapon->power);

    Slime *s2 = deepCopySlime(s);

    printf("%s %d %s %d\n", s2->name, s2->hp, s2->weapon->name, s2->weapon->power);

    //deep copy 를 제대로 했는지
    takeDamage(s,3);
    // s2->name = "slime2"; 2차로 틀림. name 은 주소를 가리키는 거지 문자열이 아님
    strcpy(s2->name, "slime2");

    printf("%s %d %s %d\n", s->name, s->hp, s->weapon->name, s->weapon->power);
    printf("%s %d %s %d\n", s2->name, s2->hp, s2->weapon->name, s2->weapon->power);

    freeSLime(s);
    freeSLime(s2);
    //3번째 실수, 입력을 넘겨주기 위해 만든 slime_Name 이랑 weapon_name 해제를 안함
    free(slime_Name);
    free(weapon_Name);

    system("pause");

    // 그런데 왜 두 개의 실수를 했는데 결과가 정상적으로 나왔냐?
    /*
    cpy_s->name = original->name; 
    여기서 두 개의 슬라임의 이름은 같은 주소를 가리키게 된 건 맞음. 하지만...
    "slime2" 같은 문자열은 데이터 영역에 이미 고정된 주소로 박혀 있는데, 
    s2->name = "slime2" 로 해버리는 순간 s2->name 포인터가 그 고정된 주소를 가리키도록 바뀜
    하지만 이렇게 되면 문제점은 이미 name 에 동적 할당을 해서 공간이 만들어졌는데,
    그 공간에는 아무것도 없이 계속 남겨지게 됨. (1차 문제)
    그리고 freeSLime 을 할 때, s2->name 을 해제하게 되는데
    s2->name 은 데이터 영역이라서 해제할 수 없음(힙 메모리만 해제 가능)
    문제가 생길 수 있음
    */

}
#ifndef _SNAKE_H_
#define _SNAKE_H_

//=== Classe que controla o jogo
class Snake {
    private:
        std::vector < Position > body;
        char head;

    public:
        //=== Membros especiais
        Snake(char h = '\u142F')
        : head( h )
        {/*empty*/}

        void update(Position new_pos);

        void set_head( char dir);
};
#endif
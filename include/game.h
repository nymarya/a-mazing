/**
 * @file game.h
 * @authors Gabriel Araújo de Souza e Mayra Dantas de Azevedo
 * @date 21 Junho 2017
 * @brief Arquivo contendo as definições da classe Game.
 */

#ifndef _GAME_H_
#define _GAME_H_

#include <iostream> //cout
#include <fstream>
#include <sstream>
#include <string>    //std::string::find
#include <algorithm>
#include <thread>    // std::this_thread::sleep_for
#include <chrono>    // std::chrono::seconds
#include <iomanip> //<! std::setw, std::setfill
#include "comum.h"
#include "snake.h"
#include "player.h"
#include "level.h"

//=== Classe que controla o jogo

/**
 * @brief      Classe para o jogo
 */
class Game
{
    //=== Membros privados
    private:
        Level level; //!< Instancia da classe Level
        Snake snake;  //!< Instancia da classe Snake
        Player player;//!< Instancia da classe Player 
        unsigned int m_levels; //!< Número de levels
    
    public:
        static const int MIN_SIZE = 1;      //<! Menor valor para linha ou coluna
        static const int MAX_SIZE = 100;     //<! Maior valor para linha ou soluna

        struct Result
        {
            bool success;
            std::string message;

            Result( bool s=true, std::string m="" ) : success(s), message(m)
            {/*empty*/}
        };

        //=== Public interface 

         /**
          * @brief      Valida a aposta informada pelo jogador
          * @param[in]  filename  Nome do arquivo contendo os níveis
          * @return     Resultado com sucesso, caso o arquivo contenha niveis validos,
          *             erro, caso contrário
          */
        Result validate ( std::string filename );

        /**
         * @brief      Inicializa os elementos do jogo
         * @param[in]  filename  Nome do arquivo contendo os níveis
         *
         */
        void initialize ( std::string filename );

        /**
         * @brief      Processa todos os eventos que ocorrem no jogo
         */
        void process_events ();

        /**
         * @brief      Atualiza todas as novas cenas do jogo
         */
        void update ();

        /**
         * @brief      Apresenta ao usuário um screshot da cena atual
         *             em que se encontra o jogo, responsável por imprimir
         *             a snake, labirinto, etc.
         */
        void render ();

        /**
         * @brief      Verifica se o jogo acabou
         *
         * @return     True se não há mais vidas, False caso contrário
         */
        bool game_over ();

};

#endif
#include <stdio.h>
#include <sqlite3.h>  // Inclui a biblioteca SQLite

int main() {
    sqlite3 *db;  // Ponteiro para o banco de dados
    char *err_msg = 0;  // Mensagem de erro (se houver)
    int rc;  // Código de retorno

    // Abre ou cria um arquivo de banco de dados chamado "players.db"
    rc = sqlite3_open("players.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao abrir o banco de dados: %s\n", sqlite3_errmsg(db));
        return rc;  // Retorna se não conseguir abrir
    }

    // Comando SQL para criar a tabela
    const char *sql = "CREATE TABLE IF NOT EXISTS players ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "nome TEXT NOT NULL, "
                      "pontuacao INTEGER NOT NULL);";

    // Executa o comando SQL
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao criar a tabela: %s\n", err_msg);
        sqlite3_free(err_msg);  // Libera a memória alocada para a mensagem de erro
    } else {
        printf("Tabela 'players' criada com sucesso.\n");
    }

    // Fecha o banco de dados
    sqlite3_close(db);

    return 0;
}
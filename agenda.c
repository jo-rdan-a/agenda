#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

// Estrutura de um contato
typedef struct Contato {
    char nome[50];
    char telefone[20];
    char email[50];
} Contato;

// Estrutura de um nó da árvore binária
typedef struct No {
    Contato contato;
    struct No* esquerda;
    struct No* direita;
} No;

// Estrutura de widgets GTK
typedef struct Widgets {
    GtkWidget* entry_nome;
    GtkWidget* entry_telefone;
    GtkWidget* entry_email;
    GtkWidget* entry_busca;
    GtkWidget* label_resultado;
    GtkWidget* box_contatos;
} Widgets;

No* raiz = NULL;

// Função para criar um novo nó da árvore
No* criarNo(char nome[], char telefone[], char email[]) {
    No* novoNo = (No*)malloc(sizeof(No));
    strcpy(novoNo->contato.nome, nome);
    strcpy(novoNo->contato.telefone, telefone);
    strcpy(novoNo->contato.email, email);
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

// Função recursiva para inserir um contato na árvore de busca binária
No* inserirBST(No* raiz, char nome[], char telefone[], char email[]) {
    if (raiz == NULL) {
        return criarNo(nome, telefone, email);  // Novo contato inserido
    }

    if (strcmp(nome, raiz->contato.nome) < 0) {
        raiz->esquerda = inserirBST(raiz->esquerda, nome, telefone, email);  // Inserir à esquerda
    } else if (strcmp(nome, raiz->contato.nome) > 0) {
        raiz->direita = inserirBST(raiz->direita, nome, telefone, email);  // Inserir à direita
    }
    return raiz;
}

// Função para atualizar a lista de contatos na interface GTK
void atualizarLista(GtkWidget* box_contatos, No* raiz) {
    GList* children = gtk_container_get_children(GTK_CONTAINER(box_contatos));
    for (GList* iter = children; iter != NULL; iter = g_list_next(iter)) {
        gtk_widget_destroy(GTK_WIDGET(iter->data));
    }
    g_list_free(children);

    if (raiz == NULL) {
        GtkWidget* label = gtk_label_new("Nenhum contato adicionado.");
        gtk_box_pack_start(GTK_BOX(box_contatos), label, FALSE, FALSE, 10);
    } else {
        // Função recursiva para percorrer a árvore e atualizar a interface
        void percorrerArvore(No* no) {
            if (no == NULL) return;
            percorrerArvore(no->esquerda);
            
            char buffer[256];
            sprintf(buffer, "Nome: %s\nTelefone: %s\nEmail: %s", no->contato.nome, no->contato.telefone, no->contato.email);
            GtkWidget* label = gtk_label_new(buffer);
            gtk_box_pack_start(GTK_BOX(box_contatos), label, FALSE, FALSE, 10);
            
            percorrerArvore(no->direita);
        }
        percorrerArvore(raiz);
    }

    gtk_widget_show_all(box_contatos);
}

// Função chamada quando o botão "Adicionar" é clicado
void adicionarContato(GtkWidget* widget, gpointer data) {
    Widgets* widgets = (Widgets*)data;
    const char* nome = gtk_entry_get_text(GTK_ENTRY(widgets->entry_nome));
    const char* telefone = gtk_entry_get_text(GTK_ENTRY(widgets->entry_telefone));
    const char* email = gtk_entry_get_text(GTK_ENTRY(widgets->entry_email));

    raiz = inserirBST(raiz, (char*)nome, (char*)telefone, (char*)email);

    gtk_entry_set_text(GTK_ENTRY(widgets->entry_nome), "");
    gtk_entry_set_text(GTK_ENTRY(widgets->entry_telefone), "");
    gtk_entry_set_text(GTK_ENTRY(widgets->entry_email), "");

    atualizarLista(widgets->box_contatos, raiz);
}

// Função recursiva para buscar um contato na árvore
No* buscarBST(No* raiz, const char* nome) {
    if (raiz == NULL || strcmp(nome, raiz->contato.nome) == 0) {
        return raiz;
    }

    if (strcmp(nome, raiz->contato.nome) < 0) {
        return buscarBST(raiz->esquerda, nome);  // Buscar à esquerda
    } else {
        return buscarBST(raiz->direita, nome);  // Buscar à direita
    }
}

// Função chamada quando o botão "Buscar" é clicado
void buscarContato(GtkWidget* widget, gpointer data) {
    Widgets* widgets = (Widgets*)data;
    const char* nome = gtk_entry_get_text(GTK_ENTRY(widgets->entry_busca));

    No* resultado = buscarBST(raiz, nome);
    char buffer[256];

    if (resultado != NULL) {
        sprintf(buffer, "Nome: %s\nTelefone: %s\nEmail: %s\n", resultado->contato.nome, resultado->contato.telefone, resultado->contato.email);
    } else {
        sprintf(buffer, "Contato não encontrado.\n");
    }

    gtk_label_set_text(GTK_LABEL(widgets->label_resultado), buffer);
}

// Função para encontrar o nó mínimo (usado na remoção)
No* encontrarMinimo(No* no) {
    while (no->esquerda != NULL) {
        no = no->esquerda;
    }
    return no;
}

// Função recursiva para remover um contato da árvore
No* removerBST(No* raiz, const char* nome) {
    if (raiz == NULL) return raiz;

    if (strcmp(nome, raiz->contato.nome) < 0) {
        raiz->esquerda = removerBST(raiz->esquerda, nome);  // Remover à esquerda
    } else if (strcmp(nome, raiz->contato.nome) > 0) {
        raiz->direita = removerBST(raiz->direita, nome);  // Remover à direita
    } else {
        // Caso 1: Nó folha
        if (raiz->esquerda == NULL && raiz->direita == NULL) {
            free(raiz);
            return NULL;
        }
        // Caso 2: Nó com um filho
        else if (raiz->esquerda == NULL) {
            No* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            No* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
        // Caso 3: Nó com dois filhos
        No* temp = encontrarMinimo(raiz->direita);
        raiz->contato = temp->contato;
        raiz->direita = removerBST(raiz->direita, temp->contato.nome);
    }
    return raiz;
}

// Função chamada quando o botão "Remover" é clicado
void removerContato(GtkWidget* widget, gpointer data) {
    Widgets* widgets = (Widgets*)data;
    const char* nome = gtk_entry_get_text(GTK_ENTRY(widgets->entry_busca));

    raiz = removerBST(raiz, nome);

    gtk_entry_set_text(GTK_ENTRY(widgets->entry_busca), "");
    atualizarLista(widgets->box_contatos, raiz);
}

// Função principal para criar a interface GTK
int main(int argc, char* argv[]) {
    gtk_init(&argc, &argv);

    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, "style.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                              GTK_STYLE_PROVIDER(provider),
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);
    
    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Agendamento de Contatos");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GdkPixbuf *icon = gdk_pixbuf_new_from_file("icon.png", NULL);
    gtk_window_set_icon(GTK_WINDOW(window), icon);
    
    Widgets* widgets = g_malloc(sizeof(Widgets));
    
    GtkWidget* grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    widgets->entry_nome = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_nome), "Nome");
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_nome, 0, 0, 1, 1);

    widgets->entry_telefone = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_telefone), "Telefone");
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_telefone, 0, 1, 1, 1);

    widgets->entry_email = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_email), "Email");
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_email, 0, 2, 1, 1);

    GtkWidget* button_adicionar = gtk_button_new_with_label("Adicionar Contato");
    g_signal_connect(button_adicionar, "clicked", G_CALLBACK(adicionarContato), widgets);
    gtk_grid_attach(GTK_GRID(grid), button_adicionar, 0, 3, 1, 1);

    widgets->box_contatos = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_grid_attach(GTK_GRID(grid), widgets->box_contatos, 0, 4, 1, 1);

    widgets->entry_busca = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_busca), "Buscar Contato");
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_busca, 1, 0, 1, 1);

    GtkWidget* button_buscar = gtk_button_new_with_label("Buscar Contato");
    g_signal_connect(button_buscar, "clicked", G_CALLBACK(buscarContato), widgets);
    gtk_grid_attach(GTK_GRID(grid), button_buscar, 1, 1, 1, 1);

    widgets->label_resultado = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), widgets->label_resultado, 1, 2, 1, 1);

    GtkWidget* button_remover = gtk_button_new_with_label("Remover Contato");
    g_signal_connect(button_remover, "clicked", G_CALLBACK(removerContato), widgets);
    gtk_grid_attach(GTK_GRID(grid), button_remover, 1, 3, 1, 1);

    atualizarLista(widgets->box_contatos, raiz);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}

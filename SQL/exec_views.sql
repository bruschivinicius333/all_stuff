-- 1. Crie uma View chamada vw_info_pedidos que encapsule a junção das tabelas principais. A View deve exibir o número do pedido, o prazo de entrega, o nome do cliente que fez o pedido e o nome do vendedor que o atendeu.
CREATE OR REPLACE VIEW vw_info_pedidos AS
SELECT p.num_ped, p.prazo_entr, c.nome_cli, v.nome_vend FROM pedido p
INNER JOIN cliente c
ON p.cd_cli = c.cod_cli
INNER JOIN vendedor v
ON v.cod_vend = p.cd_vend;
-- 2. Crie uma Função Escalar chamada fn_calcular_total_item que receba dois parâmetros numéricos (quantidade pedida e valor unitário) e retorne o valor financeiro total daquele item (a multiplicação de ambos).
CREATE OR REPLACE FUNCTION fn_calcular_total_item(quantidade_pedida FLOAT, valor_unitario FLOAT) RETURNS FLOAT
  RETURN quantidade_pedida * valor_unitario;
-- 3. Crie uma View chamada vw_faturamento_por_estado que exiba a sigla do estado (UF) e o valor financeiro total gasto pelos clientes daquele estado. (Dica: Você precisará relacionar as tabelas de Cliente, Pedido, Item do Pedido e Produto, além de usar a função de soma).
CREATE OR REPLACE VIEW vw_faturamento_por_estado AS
SELECT c.uf, SUM(i.qtd_ped * pr.val_unit) AS total_gasto FROM pedido pe
INNER JOIN cliente c
ON pe.cd_cli = c.cod_cli
INNER JOIN vendedor v
ON v.cod_vend = pe.cd_vend
INNER JOIN item_pedido i
ON pe.num_ped = i.no_ped
INNER JOIN produto pr
ON pr.cod_prod = i.cd_prod
GROUP BY c.uf;
-- 4. Crie uma Função Escalar chamada fn_classificar_prazo que receba o prazo de entrega (em dias) como parâmetro e retorne um texto (VARCHAR). Se o prazo for menor ou igual a 15 dias, a função deve retornar 'Entrega Expressa'. Caso contrário, deve retornar 'Entrega Padrão'.
CREATE OR REPLACE FUNCTION fn_classificar_prazo(prazo_entrega INT) RETURNS VARCHAR
    RETURN CASE WHEN prazo_entrega <= 15
      THEN 'Entrega Expressa'
      ELSE 'Entrega Padrão'
    END;
-- 5. Escreva uma consulta (SELECT) que utilize a View vw_info_pedidos (criada no exercício 1) e aplique a função fn_classificar_prazo (criada no exercício 4) na coluna de prazo. O resultado deve mostrar o número do pedido, o nome do cliente e a classificação do prazo.
SELECT num_ped, nome_cli, fn_classificar_prazo(prazo_entr) FROM vw_info_pedidos;
-- 6. A loja decidiu pagar uma comissão aos vendedores. Crie uma Função Escalar chamada fn_calcular_comissao que receba o valor total de uma venda como parâmetro e retorne o valor da comissão, sabendo que a taxa é de 5% sobre o valor fornecido.
CREATE OR REPLACE FUNCTION fn_calcular_comissao(total_venda FLOAT) RETURNS FLOAT
  RETURN CASE WHEN total_venda > 0
    THEN total_venda * 0.05
    ELSE 0
  END;
-- 7. Crie uma View chamada vw_desempenho_vendedores que liste o nome do vendedor, o nome do seu respectivo supervisor (se não tiver supervisor, deve exibir 'Sem Supervisor') e o valor financeiro total que esse vendedor já gerou em vendas.
CREATE OR REPLACE VIEW vw_desempenho_vendedores AS
SELECT v.nome_vend, COALESCE(
    (SELECT inner_v.nome_vend FROM vendedor inner_v WHERE inner_v.cod_vend = v.cd_supervisor LIMIT 1),
    'sem supervisor'
  ) AS supervisor,
  COALESCE((SELECT SUM(pr.val_unit * i.qtd_ped) FROM pedido pe
      INNER JOIN item_pedido i
      ON pe.num_ped = i.no_ped
      INNER JOIN produto pr
      ON pr.cod_prod = i.cd_prod
      WHERE pe.cd_vend = v.cod_vend), 0)
  AS total_vendido
FROM vendedor v;

-- 8. A partir da View vw_desempenho_vendedores (criada no exercício 7), escreva uma consulta que liste o nome do vendedor, o valor total vendido e o valor da sua comissão (utilizando obrigatoriamente a função fn_calcular_comissao do exercício 6). Ordene o resultado exibindo as maiores comissões primeiro.
SELECT nome_vend, total_vendido, fn_calcular_comissao(total_vendido) FROM vw_desempenho_vendedores
ORDER BY fn_calcular_comissao DESC;
-- 9. Crie uma View chamada vw_produtos_sem_giro que exiba o código, a descrição e o valor unitário apenas dos produtos que nunca foram vendidos (produtos que não constam em nenhum item de pedido).
CREATE OR REPLACE VIEW vw_produtos_sem_giro AS
SELECT pr.cod_prod, pr.desc_prod, pr.val_unit FROM produto pr
LEFT JOIN item_pedido i
ON pr.cod_prod = i.cd_prod
WHERE i.cd_prod IS NULL;
-- 10. Escreva uma consulta que liste o nome do cliente, o número do pedido e o valor total daquele pedido específico (você pode usar a função fn_calcular_total_item para ajudar no cálculo). Filtre o resultado para exibir apenas os pedidos cujo valor total seja estritamente superior à média do salário fixo de todos os vendedores da empresa.
SELECT c.nome_cli, pe.num_ped, fn_calcular_total_item(i.qtd_ped, pr.val_unit) FROM cliente c
INNER JOIN pedido pe
ON c.cod_cli = pe.cd_cli
INNER JOIN item_pedido i
ON pe.num_ped = i.no_ped
INNER JOIN produto pr
ON pr.cod_prod = i.cd_prod
WHERE fn_calcular_total_item(i.qtd_ped, pr.val_unit) > (SELECT AVG(sal_fixo) FROM vendedor);

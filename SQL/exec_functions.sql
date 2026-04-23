-- 1) fn_calcular_bonus_mensal: Crie uma função que receba o código de um vendedor (cod_vend). A função deve verificar a faixa de comissão dele ('A', 'B' ou 'C') e calcular um valor de bônus em Reais sobre o salário fixo (A = 10%, B = 5%, C = 2%). Retorne o valor calculado.

CREATE OR REPLACE FUNCTION fn_calcular_bonus_mensal(_cod_vend INT) RETURNS FLOAT 
AS $$
DECLARE
  salario FLOAT := (SELECT sal_fixo FROM vendedor WHERE cod_vend = _cod_vend);
  faixa_comissao VARCHAR(1) := (SELECT faixa_comiss FROM vendedor WHERE cod_vend = _cod_vend);
  multiplicador_comissao FLOAT := 0;
BEGIN
    IF faixa_comissao = 'a'
      THEN multiplicador_comissao := 0.10;
    END IF;
    IF faixa_comissao = 'b'
      THEN multiplicador_comissao := 0.05;
    END IF;
    IF faixa_comissao = 'c'
      THEN multiplicador_comissao := 0.02;
    END IF;
  RETURN (salario * multiplicador_comissao);
END;
$$ LANGUAGE PLPGSQL;

-- 2) fn_valor_total_pedido: Crie uma função que receba o número de um pedido (num_ped) e retorne o valor financeiro total desse pedido (a soma da multiplicação entre a quantidade pedida e o valor unitário de todos os itens daquele pedido). (Não confunda com a fn_calcular_total_item da lista passada, aqui queremos o total do pedido inteiro)

CREATE OR REPLACE FUNCTION fn_valor_total_pedido(_num_ped INT) RETURNS FLOAT AS $$
  BEGIN
    RETURN (
      SELECT SUM(pr.val_unit * i.qtd_ped) FROM produto pr
      INNER JOIN item_pedido i
      ON pr.cod_prod = i.cd_prod
      WHERE i.no_ped = _num_ped
    );
  END;
$$ LANGUAGE PLPGSQL;

-- 3) fn_verificar_cliente_ativo: Crie uma função que receba o código de um cliente (cod_cli) e retorne um valor Booleano (BOOLEAN). Retornará TRUE se o cliente já tiver feito algum pedido na loja, e FALSE caso nunca tenha feito nenhum pedido. 

CREATE OR REPLACE FUNCTION fn_verificar_cliente_ativo(_cod_cli INT) RETURNS BOOLEAN AS $$
  BEGIN
    IF (
      SELECT COUNT(1) FROM pedido pe
      WHERE pe.cd_cli = _cod_cli
    ) > 0
    THEN RETURN TRUE;
    END IF;
    RETURN FALSE;
  END;
$$ LANGUAGE PLPGSQL;

-- 4) sp_atualizar_salario_vendedor: Crie uma procedure que receba o código de um vendedor e um percentual de aumento (ex: 10 para 10%). A procedure deve fazer um UPDATE no salário fixo desse vendedor aplicando o aumento.

CREATE OR REPLACE PROCEDURE sp_atualizar_salario_vendedor(codigo_vendedor INT, percentual_aumento INT) AS $$
    BEGIN
        UPDATE vendedor
        SET sal_fixo = sal_fixo + (sal_fixo * (percentual_aumento * 0.01))
        WHERE cod_vend = codigo_vendedor;
    END;
$$ LANGUAGE PLPGSQL;

-- 5) sp_transferir_carteira: Crie uma procedure que receba dois parâmetros: p_vend_antigo e p_vend_novo. A procedure deve transferir todos os pedidos atrelados ao vendedor antigo para o vendedor novo (fazer um UPDATE na tabela de pedidos).

CREATE OR REPLACE PROCEDURE sp_transferir_carteira(p_vend_antigo INT, p_vend_novo INT) AS $$
BEGIN
	UPDATE pedido
	SET cd_vend = p_vend_novo
	WHERE cd_vend = p_vend_antigo;
END
$$ LANGUAGE PLPGSQL;

-- 6) sp_obter_resumo_produto: Crie uma procedure que receba o código de um produto como parâmetro de entrada (IN) e devolva a descrição do produto e o valor unitário através de dois parâmetros de saída (OUT).

CREATE OR REPLACE PROCEDURE sp_obter_resumo_produto(IN _cod_prod INT, OUT _desc_prod VARCHAR, OUT _val_unit FLOAT) AS $$ 
BEGIN
	SELECT pr.desc_prod, pr.val_unit FROM produto AS pr
	INTO _desc_prod, _val_unit
	WHERE pr.cod_prod = _cod_prod;
END
$$ LANGUAGE PLPGSQL;

-- 7) sp_excluir_cliente_seguro: Crie uma procedure que receba o código de um cliente e tente excluí-lo (DELETE). Regra: Antes de excluir, a procedure deve obrigatoriamente chamar a função fn_verificar_cliente_ativo (criada no exercício 3). Se a função retornar TRUE (ele tem pedidos), a procedure não deve fazer nada (ou lançar um erro/notice). Se retornar FALSE, o DELETE deve ser executado.

CREATE OR REPLACE PROCEDURE sp_excluir_cliente_seguro(_cod_cli INT) AS $$
	DECLARE
		isAtivo BOOLEAN := fn_verificar_cliente_ativo(_cod_cli);
	BEGIN
		IF(isAtivo IS FALSE) THEN
			DELETE FROM cliente AS c
			WHERE c.cod_cli = _cod_cli;
			RAISE NOTICE 'Excluído com sucesso!';
		ELSE 
			RAISE EXCEPTION 'Não pode excluir. Cliente possui pedidos.';	
		END IF;
	END;
$$ LANGUAGE PLPGSQL;


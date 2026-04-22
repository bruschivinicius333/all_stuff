-- 1
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

-- 2
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

-- 3
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

import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

import org.junit.Test;

public class ValidadorSenhaTest {

    @Test
    public void Teste_SeClasseExiste() {
        ValidadorSenha validador = new ValidadorSenha();
        assertTrue(validador != null);
    }

    @Test
    public void Teste_SenhaComMenosDe8Caracteres() {
        ValidadorSenha validador = new ValidadorSenha();

        assertFalse(validador.isValid("A1@b"));    //menos de 8 caracteres
        assertTrue(validador.isValid("A1@bcdef")); //exatamente 8 caracteres
        assertTrue(validador.isValid("A1@bcdefg")); //mais de 8 
    }

    @Test
    public void Teste_SenhaSemNumeros() {
        ValidadorSenha validador = new ValidadorSenha();

        assertFalse(validador.isValid("A@bcdefg"));  //sem números
        assertTrue(validador.isValid("A1@bcdefg"));  //com um número
        assertTrue(validador.isValid("A123@bcd!"));  //com vários números
    }

    @Test
    public void Teste_SenhaSemCaracteresEspeciais() {
        ValidadorSenha validador = new ValidadorSenha();

        assertFalse(validador.isValid("A1bcdefg"));  //sem caracteres especiais
        assertTrue(validador.isValid("A1@bcdef"));   //com um caractere especial
        assertTrue(validador.isValid("A1@!#defg"));  //com vários caracteres 
    }

    @Test
    public void Teste_SenhaSemLetrasMaiusculas() {
        ValidadorSenha validador = new ValidadorSenha();

        assertFalse(validador.isValid("a1@bcdefg"));  //sem letras maiúsculas
        assertTrue(validador.isValid("A1@bcdefg"));   //com uma letra maiúscula
        assertTrue(validador.isValid("AB1@defg"));    //com várias letras maiúsculas
    }

    @Test
    public void Teste_SenhaValida() {
        ValidadorSenha validador = new ValidadorSenha();

        assertTrue(validador.isValid("A1@bcdefg"));   //senha válida
        assertTrue(validador.isValid("A1@Bcdef123!")); //senha longa válida
    }

    @Test
    public void Teste_CasosLimite() {
        ValidadorSenha validador = new ValidadorSenha();

        assertFalse("Senha vazia deve ser inválida", validador.isValid(""));  // senha vazia

        assertFalse("Senha sem caractere especial e maiúscula deve ser inválida", validador.isValid("abc12345")); // sem caractere especial e maiúscula

        assertFalse("Senha com espaço extra no final deve ser inválida", validador.isValid("Abc12345@ ")); // espaço extra no final
        
        assertFalse("Senha com menos de 8 caracteres deve ser inválida", validador.isValid("A1@b"));  // senha com menos de 8 caracteres
    }

    
}

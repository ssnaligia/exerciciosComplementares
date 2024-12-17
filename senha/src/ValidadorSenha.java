public class ValidadorSenha {

    public boolean isValid(String senha) {
        if (senha == null || senha.trim().length() < 8) {
            return false; 
        }

        if (!senha.equals(senha.trim())) {
            return false;  
        }

        boolean temNumero = senha.matches(".*\\d.*");
        boolean temEspecial = senha.matches(".*[!@#$%^&*()-+=].*");
        boolean temMaiuscula = senha.matches(".*[A-Z].*");

        return temNumero && temEspecial && temMaiuscula;
    }
}

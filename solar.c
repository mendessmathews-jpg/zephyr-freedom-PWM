/*
 * ============================================================
 *  INCIDÊNCIA SOLAR - GEOMETRIA SOLAR
 *  São Paulo | β = 23,57° | γ = 170° (voltada para Norte)
 *
 *  Exercício:
 *  1) 1 dia por mês → ângulo de incidência θ ao meio-dia
 *  2) Dia escolhido (junho/21) → θ hora a hora (8h–16h)
 * ============================================================
 */

#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

/* ---------- Parâmetros do local e da placa ---------- */
#define LAT      -23.57   /* latitude φ (°) — negativo = Sul     */
#define LONG      46.73   /* longitude L  (°) — Oeste            */
#define L0        45.0    /* longitude hora legal (°)             */
#define BETA      23.57   /* inclinação da placa β (°)            */
#define GAMMA    170.0    /* azimute da placa  γ (°)              */

/* ---------- Conversões ---------- */
double grau2rad(double g) { return g * PI / 180.0; }
double rad2grau(double r) { return r * 180.0 / PI; }

/* -------------------------------------------------------
 *  Eq. 9.1 — Dia do ano  n
 * ----------------------------------------------------- */
int dia_do_ano(int dia, int mes) {
    int cor;
    if      (mes <= 2)            cor = mes / 2;
    else if (mes > 2 && mes <= 8) cor = (mes / 2) - 2;
    else                          cor = (int)(mes / 2.0 + 0.5) - 2;
    return dia + (mes - 1) * 30 + cor;
}

/* -------------------------------------------------------
 *  Eq. 9.2 — Declinação solar  δ (graus)
 * ----------------------------------------------------- */
double declinacao(int n) {
    return 23.45 * sin(grau2rad(360.0 / 365.0 * (284 + n)));
}

/* -------------------------------------------------------
 *  Eq. 9.5/9.6 — Equação do tempo E e fator B
 * ----------------------------------------------------- */
double equacao_tempo(int n) {
    double B = grau2rad((360.0 / 364.0) * (n - 81));
    return 9.87 * sin(2 * B) - 7.53 * cos(B) - 1.5 * sin(B);
}

/* -------------------------------------------------------
 *  Eq. 9.3/9.4 — Hora solar  HS
 * ----------------------------------------------------- */
double hora_solar(double HL, int n) {
    double E       = equacao_tempo(n);
    double corhora = (4.0 * (L0 - LONG) + E) / 60.0;
    return HL + corhora;
}

/* -------------------------------------------------------
 *  Eq. 9.7 — Ângulo horário  ω (graus)
 * ----------------------------------------------------- */
double angulo_horario(double HS) {
    return (HS - 12.0) * 15.0;
}

/* -------------------------------------------------------
 *  Eq. 9.8/9.9 — Pôr do sol  ωs e duração  N
 * ----------------------------------------------------- */
double por_do_sol(double delta_g, double phi_g) {
    double t = -tan(grau2rad(phi_g)) * tan(grau2rad(delta_g));
    if (t >  1.0) t =  1.0;  /* evita domínio do acos */
    if (t < -1.0) t = -1.0;
    return rad2grau(acos(t));
}

double duracao_insolacao(double omega_s) {
    return (2.0 / 15.0) * omega_s;
}

/* -------------------------------------------------------
 *  Eq. 9.10 — Ângulo zenital  θz (graus)
 * ----------------------------------------------------- */
double angulo_zenital(double delta_g, double phi_g, double omega_g) {
    double d = grau2rad(delta_g);
    double p = grau2rad(phi_g);
    double w = grau2rad(omega_g);
    double cos_tz = sin(d)*sin(p) + cos(d)*cos(p)*cos(w);
    if (cos_tz >  1.0) cos_tz =  1.0;
    if (cos_tz < -1.0) cos_tz = -1.0;
    return rad2grau(acos(cos_tz));
}

/* -------------------------------------------------------
 *  Eq. 9.15 — Ângulo de incidência sobre a placa  θ (graus)
 * ----------------------------------------------------- */
double angulo_incidencia(double delta_g, double phi_g,
                         double omega_g, double beta_g, double gamma_g) {
    double d  = grau2rad(delta_g);
    double p  = grau2rad(phi_g);
    double w  = grau2rad(omega_g);
    double b  = grau2rad(beta_g);
    double gm = grau2rad(gamma_g);

    double cos_theta =
          sin(d)*sin(p)*cos(b)
        - sin(d)*cos(p)*sin(b)*cos(gm)
        + cos(d)*cos(p)*cos(b)*cos(w)
        + cos(d)*sin(p)*sin(b)*cos(gm)*cos(w)
        + cos(d)*sin(b)*sin(gm)*sin(w);

    if (cos_theta >  1.0) cos_theta =  1.0;
    if (cos_theta < -1.0) cos_theta = -1.0;
    return rad2grau(acos(cos_theta));
}

/* -------------------------------------------------------
 *  Avalia se o sol está acima do horizonte
 * ----------------------------------------------------- */
int sol_visivel(double theta_z) {
    return theta_z < 90.0;
}

/* ============================================================
 *  MAIN
 * ========================================================== */
int main(void) {

    /* Dias representativos de cada mês (15 de cada mês) */
    int dias_mes[12]  = {15, 15, 15, 15, 15, 15,
                         15, 15, 15, 15, 15, 15};
    int meses[12]     = { 1,  2,  3,  4,  5,  6,
                          7,  8,  9, 10, 11, 12};
    const char *nomes[12] = {
        "Janeiro  ","Fevereiro","Marco    ","Abril    ",
        "Maio     ","Junho    ","Julho    ","Agosto   ",
        "Setembro ","Outubro  ","Novembro ","Dezembro "
    };

    double HL_meiodia = 12.0;   /* hora legal do meio-dia */

    printf("============================================================\n");
    printf("  INCIDENCIA SOLAR - SAO PAULO\n");
    printf("  Placa: beta=%.2f graus | gama=%.1f graus\n", BETA, GAMMA);
    printf("  Latitude: %.2f  Longitude: %.2f\n", LAT, LONG);
    printf("============================================================\n\n");

    /* =========================================================
     *  PARTE 1 — θ ao meio-dia para 1 dia de cada mês
     * ======================================================= */
    printf("----------------------------------------------------------\n");
    printf("  PARTE 1: Angulo de incidencia ao meio-dia (12h legal)\n");
    printf("----------------------------------------------------------\n");
    printf("  %-10s  %4s  %5s  %7s  %7s  %7s  %6s\n",
           "Mes", "n", "delta", "HS", "omega", "theta_z", "theta");
    printf("  %-10s  %4s  %5s  %7s  %7s  %7s  %6s\n",
           "---", "---", "(grau)", "(h)", "(grau)", "(grau)", "(grau)");
    printf("  -------------------------------------------------------\n");

    int dia_escolhido_n = 0;
    double delta_esc = 0, omega_esc = 0;

    for (int i = 0; i < 12; i++) {
        int n      = dia_do_ano(dias_mes[i], meses[i]);
        double del = declinacao(n);
        double HS  = hora_solar(HL_meiodia, n);
        double w   = angulo_horario(HS);
        double tz  = angulo_zenital(del, LAT, w);
        double th  = angulo_incidencia(del, LAT, w, BETA, GAMMA);
        double ws  = por_do_sol(del, LAT);
        double N   = duracao_insolacao(ws);

        printf("  %-10s  %4d  %5.2f  %7.4f  %7.2f  %7.2f  %6.2f",
               nomes[i], n, del, HS, w, tz,
               sol_visivel(tz) ? th : 999.0);

        if (!sol_visivel(tz))
            printf("  [SEM SOL]");
        printf("\n");

        /* Escolhe junho como dia de referência para a Parte 2 */
        if (meses[i] == 6) {
            dia_escolhido_n = n;
            delta_esc       = del;
        }
    }

    /* =========================================================
     *  PARTE 2 — θ hora a hora (8h–16h) para junho/15
     * ======================================================= */
    printf("\n----------------------------------------------------------\n");
    printf("  PARTE 2: Hora a hora — Dia 15 de Junho (n=%d)\n",
           dia_escolhido_n);
    printf("  delta = %.2f graus\n", delta_esc);
    printf("----------------------------------------------------------\n");

    double ws_esc = por_do_sol(delta_esc, LAT);
    double N_esc  = duracao_insolacao(ws_esc);
    printf("  Por do sol: ws = %.2f grau  |  Duracao do dia: N = %.2f h\n\n",
           ws_esc, N_esc);

    printf("  %6s  %7s  %7s  %7s  %8s  %8s  %8s  %-12s\n",
           "HL(h)", "HS(h)", "omega", "delta", "theta_z",
           "alfa", "theta", "Situacao");
    printf("  %6s  %7s  %7s  %7s  %8s  %8s  %8s\n",
           "------","------","------","------","------","------","------");

    for (int h = 8; h <= 16; h++) {
        double HL  = (double)h;
        double HS  = hora_solar(HL, dia_escolhido_n);
        double w   = angulo_horario(HS);
        double tz  = angulo_zenital(delta_esc, LAT, w);
        double alfa = 90.0 - tz;
        double th  = angulo_incidencia(delta_esc, LAT, w, BETA, GAMMA);

        const char *status;
        if (!sol_visivel(tz))
            status = "** SEM SOL **";
        else if (th <= 10.0)
            status = "Otimo (quase perp.)";
        else if (th <= 30.0)
            status = "Muito bom";
        else if (th <= 50.0)
            status = "Bom";
        else if (th <= 70.0)
            status = "Regular";
        else
            status = "Baixa incidencia";

        printf("  %6.0f  %7.4f  %7.2f  %7.2f  %8.2f  %8.2f  %8.2f  %s\n",
               HL, HS, w, delta_esc, tz, alfa,
               sol_visivel(tz) ? th : 999.0,
               status);
    }

    printf("\n============================================================\n");
    printf("  LEGENDA\n");
    printf("  n      = dia do ano\n");
    printf("  delta  = declinacao solar (graus)\n");
    printf("  HS     = hora solar (h)\n");
    printf("  omega  = angulo horario (graus, neg=manha, pos=tarde)\n");
    printf("  theta_z= angulo zenital (0=sol a pino, 90=horizonte)\n");
    printf("  alfa   = altitude solar = 90 - theta_z\n");
    printf("  theta  = angulo de incidencia sobre a placa\n");
    printf("           (quanto menor, melhor a captacao)\n");
    printf("  999    = sol abaixo do horizonte (sem radiacao direta)\n");
    printf("============================================================\n");

    return 0;
}
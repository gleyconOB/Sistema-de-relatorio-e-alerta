import requests
import datetime

# URL do endpoint do Google Apps Script
url = "https://script.google.com/macros/s/AKfycbzS9GbL3tBV5PjC5FDSHdPyQot-DFDeVWg182EBrKJCedOSWxIwGREqf8dOEdvUWvi6/exec"

# Função para enviar dados
def enviar_dados(temperatura, alerta):
    data = {
        "temperatura": temperatura,
        "alerta": alerta
    }
    # Envia uma requisição POST para o Google Sheets com os dados em JSON
    response = requests.post(url, json=data)
    if response.status_code == 200:
        print("Dados enviados com sucesso!")
    else:
        print("Erro ao enviar os dados:", response.text)

# Exemplo de envio de dados
temperatura = -1.5  # Simulação de temperatura
alerta = "Refrigerador com problema" if temperatura != -2 else "Normal"
enviar_dados(temperatura, alerta)
import sys

def hex_to_rgb565(hex_color: str) -> int:
    # Supprime le '#' si présent
    hex_color = hex_color.lstrip('#')
    if len(hex_color) != 6:
        raise ValueError("Le format hexadécimal doit être RRGGBB (6 caractères).")

    # Convertit chaque composante
    r = int(hex_color[0:2], 16)
    g = int(hex_color[2:4], 16)
    b = int(hex_color[4:6], 16)

    # Convertit en RGB 565
    r_565 = (r >> 3) & 0x1F
    g_565 = (g >> 2) & 0x3F
    b_565 = (b >> 3) & 0x1F

    return (r_565 << 11) | (g_565 << 5) | b_565

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <couleur_hex>")
        print("Exemple: python script.py FF00FF")
        sys.exit(1)

    try:
        hex_color = sys.argv[1].upper()
        rgb565 = hex_to_rgb565(hex_color)
        print(f"Couleur #{hex_color} en RGB 565 : 0x{rgb565:04X} ({rgb565})")
    except ValueError as e:
        print(f"Erreur : {e}")
        sys.exit(1)

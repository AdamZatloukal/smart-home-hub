export const hexToRGB = (hex: string) => {
  hex = hex.startsWith("#") ? hex.slice(1) : hex;
  
  if (hex.length === 3) {
    hex = Array.from(hex).reduce((str, x) => str + x + x, "");
  }

  const values = hex
    .split(/([a-z0-9]{2,2})/)
    .filter(Boolean)
    .map((x) => parseInt(x, 16));

  return {
    red: values[0],
    green: values[1],
    blue: values[2],
  };
};
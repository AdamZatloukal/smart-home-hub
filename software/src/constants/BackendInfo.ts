const IP = "10.0.0.6";

export const backend = {
    backEndIP: IP,
    postUrlColor: `http://${IP}/set/color`,
    postUrlBrightness: `http://${IP}/set/brightness`,
    postUrlSpeed: `http://${IP}/set/speed`,
    postUrlMode: `http://${IP}/set/mode`
} 
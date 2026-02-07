import { StyleSheet } from "react-native";
import { Fonts } from "../constants/Fonts";

export const styles = StyleSheet.create({
    container: {
        height: 135,
        width: 350,
        borderRadius: 20,
    },
    dashboard: {
        flex: 1
    },
    titleContainer: {
        padding: 10,
        marginLeft: 15,
        marginRight: 15,
        marginTop: 10
    },
    welcomeTitle: {
        fontFamily: Fonts.normalText,
        fontSize: 20
    },
    catchphrase: {
        fontFamily: Fonts.mediumText,
        fontSize: 30,
    },
});
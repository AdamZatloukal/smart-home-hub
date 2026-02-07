import { StyleSheet } from "react-native";
import { Fonts } from "../constants/Fonts";

export const styles = StyleSheet.create({
    dashboard: {
        flex: 0.5,
        marginBottom: 180,
        height: 300
    },
    titleContainer: {
        padding: 10,
        marginLeft: 15,
        marginRight: 15,
        marginTop: 10
    },
    catchphrase: {
        fontFamily: Fonts.mediumText,
        fontSize: 30,
    },
    dashboardContainer: {
        width: 350,
        height: 120,
        flexDirection: "row"
    },
    dashboardMain: {
        height:120,
        width: 240,
        backgroundColor: "#f5f6fa",
        borderTopLeftRadius: 25,
        borderTopRightRadius: 0,
        borderBottomLeftRadius: 25,
        borderBottomRightRadius: 0,
        padding: 10,
        alignItems: "flex-start",
        justifyContent:"center"
    },
    dashboardColor: {
        height:120,
        width:110,
        backgroundColor: "yellow",
        borderTopLeftRadius: 0,
        borderTopRightRadius: 25,
        borderBottomLeftRadius: 0,
        borderBottomRightRadius: 25,
        padding: 2,
        alignItems:"flex-end",
        justifyContent:"flex-end"
    },
    colorTitleText: {
        fontSize: 15,
        fontFamily: Fonts.normalText
    },
    colorText: {    
        fontFamily: Fonts.semiboldText,
        fontSize: 30
    },
    switchContainer: {
    },
    heartContainer: {
        height: 40,
        width:40,
        marginBottom: 25,
        marginRight: 10
    }
});
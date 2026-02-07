import { StyleSheet } from "react-native";
import { Colors } from "../constants/Colors";
import { Fonts } from "../constants/Fonts";

export const styles = StyleSheet.create({
  settingContainer: {
    backgroundColor: Colors.settingBackground,
    width: 370,
    height: 190,
    borderRadius: 25,
    borderBottomRightRadius: 40,
    marginLeft: 15,
    marginBottom: 10
  },
  settingContainerInner: {
    backgroundColor: Colors.applianceCard,
    width:350,
    height: 170,
    borderRadius: 25,
    justifyContent:"space-between",
    alignItems: "center"
  },
  settingName: {
    alignSelf:"flex-start",
    margin: 20,
    marginTop: 10,
    fontFamily: Fonts.semiboldText,
    fontSize: 20
  },
  expandIcon: {
    alignSelf:"flex-end",
    padding: 10,  
    position: "absolute",
    marginTop: 120
  }
});
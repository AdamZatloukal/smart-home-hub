import { Colors } from "@/src/constants/Colors";
import { StyleSheet } from "react-native";

export const Styles = StyleSheet.create({
  card: {
    backgroundColor: Colors.applianceCard,
    width: 180,
    height: 180,
    borderRadius: 20,
    padding: 15,
    margin: 15,
    justifyContent: "flex-start",
    
  },
  app: {
    flex: 1,
    backgroundColor: Colors.screenBackground
  },
  title: {
    fontSize: 22,
    paddingTop: 5,
    fontFamily: "Inter_400Regular"
  },
  iconContainer: {
    width: 30,
    height: 30,
    borderRadius: 7,
    justifyContent: "center",
    alignItems: "center"
  },
  icon: {
    width: 30,
    height: 30
  },
  switchContainer: {
    alignItems: "flex-start",
  },
  visualElement: {
    width: 120,
    height: 50
  },
  visualElementInner1: {
    backgroundColor: Colors.yellowExtra,
    marginTop: 8,
    height: 15,
    width: 90,
    borderRadius: 25
  },
  visualElementInner2: {
     backgroundColor: Colors.darkBlueExtra,
    marginTop: 8,
    height: 15,
    width: 50,
    borderRadius: 25
  }
});
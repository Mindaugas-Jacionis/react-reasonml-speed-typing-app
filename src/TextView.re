module Styles = {
  let container =
    ReactDOMRe.Style.make(
      ~fontSize="22px",
      ~lineHeight="36px",
      ~textAlign="justify",
      ~padding="50px 0px",
      (),
    );
};

let component = ReasonReact.statelessComponent("TextView");

let renderWords = wordsArray =>
  Array.map(
    word => <span> {ReasonReact.string(word ++ " ")} </span>,
    wordsArray,
  );

let make = (_children, ~words) => {
  ...component,
  render: _self =>
    <div style=Styles.container> ...{renderWords(words)} </div>,
};